#pragma once

// Buffer layout (all little-endian, no explicit byte-order conversion):
//
//   [ uint32_t count ]
//   [ Entry[0] .. Entry[count-1] ]   ← directory, sorted ascending by key
//   [ value bytes … ]                ← data section, offsets relative to its start
//
// Entry (20 bytes, naturally aligned):
//   int64_t   key
//   uint32_t  data_offset   ← byte offset into the data section
//   uint32_t  data_size     ← byte length of the value
//   uint8_t   type          ← ValueType tag
//   uint8_t   _pad[3]       ← explicit padding so sizeof(Entry)==20
//
// Because data_offset is relative to the data section, inserting a new
// directory entry (which shifts the data section by sizeof(Entry) bytes)
// never requires patching existing offsets.
//
// Complexity:
//   contains / type_of / get  — O(log n)  binary search
//   insert / update           — O(n)      memmove to maintain sorted order
//                                         (acceptable per spec; no memory constraints)

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

class FlatMap {
public:
    // ------------------------------------------------------------------
    // Public types
    // ------------------------------------------------------------------

    enum class ValueType : uint8_t {
        Int64       = 0,
        Float64     = 1,
        String      = 2,
        Bool        = 3,
        Timestamp   = 4
    };

    // Returned by get(); callers use std::visit or std::get<T>
    using Value = std::variant<int64_t, double, std::string>;

    // ------------------------------------------------------------------
    // Construction / serialisation
    // ------------------------------------------------------------------

    /// Default: empty map (4-byte header, count = 0).
    FlatMap() {
        buf_.resize(HDR_SIZE, std::byte{0});
    }

    /// Deserialise from a raw blob (e.g. loaded from disk).
    /// The blob is validated minimally; no deep integrity check is performed.
    explicit FlatMap(std::vector<std::byte> blob) : buf_(std::move(blob)) {
        if (buf_.size() < HDR_SIZE)
            throw std::invalid_argument("FlatMap: buffer too small to hold header");
        // Sanity: declared entry count must fit within the buffer.
        const uint32_t n = count();
        const size_t min_size = HDR_SIZE + static_cast<size_t>(n) * ENTRY_SIZE;
        if (buf_.size() < min_size)
            throw std::invalid_argument("FlatMap: buffer truncated (directory overflows buffer)");
    }

    /// The backing buffer IS the serialised form — no additional encoding.
    /// Write raw_bytes() to a file; reconstruct with FlatMap(vector<byte>).
    [[nodiscard]] std::span<const std::byte> raw_bytes() const noexcept { return buf_; }
    [[nodiscard]] const std::vector<std::byte>& buffer()  const noexcept { return buf_; }

    // ------------------------------------------------------------------
    // Capacity / diagnostics
    // ------------------------------------------------------------------

    [[nodiscard]] uint32_t size()      const noexcept { return count(); }
    [[nodiscard]] bool     empty()     const noexcept { return count() == 0; }
    [[nodiscard]] size_t   byte_size() const noexcept { return buf_.size(); }

    // ------------------------------------------------------------------
    // Mutation: insert or overwrite
    // ------------------------------------------------------------------

    void insert(int64_t key, int64_t value) {
        write_value(key, ValueType::Int64,
                    reinterpret_cast<const std::byte*>(&value), sizeof value);
    }

    void insert(int64_t key, double value) {
        write_value(key, ValueType::Float64,
                    reinterpret_cast<const std::byte*>(&value), sizeof value);
    }

    void insert(int64_t key, std::string_view value) {
        write_value(key, ValueType::String,
                    reinterpret_cast<const std::byte*>(value.data()),
                    static_cast<uint32_t>(value.size()));
    }

    void insert(const int64_t key, const bool value) {
        const int64_t i64 = value? 1l : 0l;
        write_value(key, ValueType::Bool, reinterpret_cast<const std::byte*>(&i64), sizeof i64);
    }

    void insert_timestamp(const int64_t key, const int64_t value) {
        write_value(key, ValueType::Timestamp, reinterpret_cast<const std::byte*>(&value), sizeof value);
    }

    // ------------------------------------------------------------------
    // Query
    // ------------------------------------------------------------------

    /// True iff key is present.
    [[nodiscard]] bool contains(int64_t key) const noexcept {
        return find_idx(key).first;
    }

    /// Returns the ValueType stored at key, or nullopt if absent.
    [[nodiscard]] std::optional<ValueType> type_of(int64_t key) const noexcept {
        auto [found, pos] = find_idx(key);
        if (!found) return std::nullopt;
        return entry_at(pos).type;
    }

    /// Returns the value stored at key, or nullopt if absent.
    /// The returned variant is one of: int64_t, double, std::string.
    [[nodiscard]] std::optional<Value> get(int64_t key) const {
        auto [found, pos] = find_idx(key);
        if (!found) return std::nullopt;

        const Entry& e = entry_at(pos);
        const std::byte* d = data_section() + e.data_offset;

        switch (e.type) {
        case ValueType::Int64:
        case ValueType::Timestamp:
        case ValueType::Bool:{
            int64_t v{};
            std::memcpy(&v, d, sizeof v);
            return v;
        }
        case ValueType::Float64: {
            double v{};
            std::memcpy(&v, d, sizeof v);
            return v;
        }
        case ValueType::String:
            return std::string(reinterpret_cast<const char*>(d), e.data_size);
        }
        // Unreachable in valid data; explicit return to silence warnings.
        throw std::logic_error("FlatMap: unknown ValueType tag");
    }

    [[nodiscard]] bool get_bool(const int64_t key) const noexcept {
        auto [found, pos] = find_idx(key);
        const Entry& e = entry_at(pos);
        const std::byte* d = data_section() + e.data_offset;

        int64_t v{};
        std::memcpy(&v, d, sizeof v);
        return v != 0l;
    }

    [[nodiscard]] int64_t get_int(const int64_t key) const noexcept {
        auto [found, pos] = find_idx(key);
        const Entry& e = entry_at(pos);
        const std::byte* d = data_section() + e.data_offset;

        int64_t v{};
        std::memcpy(&v, d, sizeof v);
        return v;
    }

    [[nodiscard]] double get_real(const int64_t key) const noexcept {
        auto [found, pos] = find_idx(key);
        const Entry& e = entry_at(pos);
        const std::byte* d = data_section() + e.data_offset;

        double v{};
        std::memcpy(&v, d, sizeof v);
        return v;
    }

    [[nodiscard]] std::string_view get_string(const int64_t key) const noexcept {
        auto [found, pos] = find_idx(key);
        const Entry& e = entry_at(pos);
        const std::byte* d = data_section() + e.data_offset;

        const std::string_view v(reinterpret_cast<const char*>(d), e.data_size);
        return v;
    }
private:
    // ------------------------------------------------------------------
    // Internal layout constants
    // ------------------------------------------------------------------

    struct alignas(16) Entry {
        int64_t   key;          //  8 B
        uint32_t  data_offset;  //  4 B  — relative to start of data section
        uint16_t  data_size;    //  2 B  — in bytes
        ValueType type;         //  1 B
        uint8_t   _pad[1]{};   //  1 B  — explicit padding; sizeof == 16
    };
    static_assert(sizeof(Entry) == 16, "Entry layout changed — update ENTRY_SIZE");

    static constexpr size_t HDR_SIZE  = sizeof(uint32_t);
    static constexpr size_t ENTRY_SIZE = sizeof(Entry);

    std::vector<std::byte> buf_;

    // ------------------------------------------------------------------
    // Raw buffer accessors (always recomputed after any buf_ mutation)
    // ------------------------------------------------------------------

    [[nodiscard]] uint32_t count() const noexcept {
        uint32_t n{};
        std::memcpy(&n, buf_.data(), sizeof n);
        return n;
    }
    void set_count(const uint32_t n) noexcept {
        std::memcpy(buf_.data(), &n, sizeof n);
    }

    [[nodiscard]] size_t data_sec_start() const noexcept {
        return HDR_SIZE + static_cast<size_t>(count()) * ENTRY_SIZE;
    }
    [[nodiscard]] size_t data_sec_size() const noexcept {
        return buf_.size() - data_sec_start();
    }

    [[nodiscard]] const Entry& entry_at(const size_t i) const noexcept {
        return reinterpret_cast<const Entry*>(buf_.data() + HDR_SIZE)[i];
    }
    [[nodiscard]] Entry& entry_at(const size_t i) noexcept {
        return reinterpret_cast<Entry*>(buf_.data() + HDR_SIZE)[i];
    }

    [[nodiscard]] const std::byte* data_section() const noexcept {
        return buf_.data() + data_sec_start();
    }
    [[nodiscard]] std::byte* data_section() noexcept {
        return buf_.data() + data_sec_start();
    }

    // ------------------------------------------------------------------
    // Binary search — O(log n)
    // Returns {found, index}.  If !found, index is the insertion position.
    // ------------------------------------------------------------------

    [[nodiscard]] std::pair<bool, size_t> find_idx(int64_t key) const noexcept {
        const uint32_t n = count();
        size_t lo = 0, hi = n;
        while (lo < hi) {
            const size_t mid = lo + (hi - lo) / 2;
            const int64_t k  = entry_at(mid).key;
            if (k == key) return {true,  mid};
            if (k  < key) lo = mid + 1;
            else          hi = mid;
        }
        return {false, lo};
    }

    // ------------------------------------------------------------------
    // Core write path
    // ------------------------------------------------------------------

    void write_value(int64_t key, ValueType vt,
                     const std::byte* data, uint32_t dsz) {
        auto [found, pos] = find_idx(key);
        if (found) raw_update(pos, vt, data, dsz);
        else       raw_insert(pos, key, vt, data, dsz);
    }

    // Insert a brand-new key at sorted position `pos`.
    //
    // Memory operations (in order, all using buf_.data() re-fetched after resize):
    //   1. Resize the buffer to accommodate one new Entry + dsz data bytes.
    //   2. Slide the whole data section right by ENTRY_SIZE bytes, opening a
    //      slot in the directory without invalidating any relative data_offset.
    //   3. Slide directory entries [pos, count) right by one slot.
    //   4. Write the new Entry at position pos.
    //   5. Append value bytes at the end of the data section.
    //   6. Increment count.
    void raw_insert(size_t pos, int64_t key, ValueType vt,
                    const std::byte* data, uint32_t dsz) {
        const uint32_t n          = count();
        const size_t   old_dsec   = data_sec_start(); // before resize
        const size_t   old_ds_sz  = data_sec_size();
        const uint32_t new_doff   = static_cast<uint32_t>(old_ds_sz); // append

        // 1. Grow buffer
        buf_.resize(buf_.size() + ENTRY_SIZE + dsz);
        std::byte* b = buf_.data(); // re-fetch after potential realloc

        // 2. Slide data section right by ENTRY_SIZE
        std::memmove(b + old_dsec + ENTRY_SIZE,
                     b + old_dsec,
                     old_ds_sz);

        // 3. Slide directory entries [pos, n) right by one slot
        if (pos < n) {
            std::memmove(b + HDR_SIZE + (pos + 1) * ENTRY_SIZE,
                         b + HDR_SIZE +  pos      * ENTRY_SIZE,
                         (n - pos) * ENTRY_SIZE);
        }

        // 4. Write the new directory entry
        Entry e{};
        e.key         = key;
        e.data_offset = new_doff;
        e.data_size   = dsz;
        e.type        = vt;
        std::memcpy(b + HDR_SIZE + pos * ENTRY_SIZE, &e, ENTRY_SIZE);

        // 5. Copy value bytes into the data section
        //    New data section starts at HDR_SIZE + (n+1)*ENTRY_SIZE
        std::byte* new_dsec = b + HDR_SIZE + (n + 1) * ENTRY_SIZE;
        std::memcpy(new_dsec + new_doff, data, dsz);

        // 6. Bump count
        set_count(n + 1);
    }

    // Overwrite an existing key's value at directory index `pos`.
    //
    // If the new value is the same byte size as the old one, we update
    // in-place (no structural changes to the buffer).
    //
    // Otherwise we excise the old bytes from the data section, patch the
    // offsets of all subsequent entries, then append the new bytes at the end.
    void raw_update(size_t pos, ValueType vt,
                    const std::byte* data, uint32_t dsz) {
        const Entry&  e       = entry_at(pos);
        const uint32_t old_off = e.data_offset;
        const uint32_t old_sz  = e.data_size;

        if (dsz == old_sz) {
            // Fast path: same size, overwrite in place
            std::memcpy(data_section() + old_off, data, dsz);
            entry_at(pos).type = vt;
            return;
        }

        // Slow path: size changed — excise old bytes, append new bytes.
        const size_t dso      = data_sec_start();
        const size_t total_ds = data_sec_size();
        const uint32_t n      = count();

        // Remove old bytes by shifting the tail of the data section left
        std::byte* ds = buf_.data() + dso;
        const size_t after = old_off + old_sz;
        std::memmove(ds + old_off, ds + after, total_ds - after);
        buf_.resize(buf_.size() - old_sz);

        // Patch data_offsets: every entry whose data lives after the removed
        // block must have its offset decremented by old_sz.
        // (Note: entry at pos has data_offset == old_off, condition is >, not >=)
        for (uint32_t i = 0; i < n; ++i) {
            if (entry_at(i).data_offset > old_off)
                entry_at(i).data_offset -= old_sz;
        }

        // Append new bytes at the end of the (now-smaller) data section
        const uint32_t new_off = static_cast<uint32_t>(data_sec_size());
        buf_.resize(buf_.size() + dsz);
        // Re-fetch data section pointer after resize (potential realloc)
        std::memcpy(buf_.data() + data_sec_start() + new_off, data, dsz);

        // Update the target entry (re-fetch after resize)
        Entry& ee      = entry_at(pos);
        ee.data_offset = new_off;
        ee.data_size   = dsz;
        ee.type        = vt;
    }
};