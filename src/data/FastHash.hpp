#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <cstring>
#include <stdexcept>
#include <absl/container/flat_hash_map.h>

class FlatMap {
private:
	absl::flat_hash_map<std::string, uint64_t> str_to_id_;
	absl::flat_hash_map<uint64_t, std::string> id_to_str_;
public:
    FlatMap() = default;
    uint64_t add(std::string_view str) {
        auto it = str_to_id_.find(str);
        if (it != str_to_id_.end()) {
            return it->second;
        }
        uint64_t id = str_to_id_.size();
        str_to_id_[str] = id;
        id_to_str_[id] = str;
        return id;
    }
    std::string get_string(uint64_t id) const {
        auto it = id_to_str_.find(id);
        if (it != id_to_str_.end()) {
            return it->second;
        }
        return {};
    }
    int64_t get_index(std::string_view str) const {
        auto it = str_to_id_.find(str);
        if (it != str_to_id_.end()) {
            return it->second;
        }
        return -1;
    }
	size_t size() const { return str_to_id_.size(); }
};


template <size_t BufferSize = 2048>
class EmbeddedFlatMap {
public:
    static constexpr size_t MAX_KEYS = 256;
    static constexpr size_t HASH_TABLE_SIZE = 512; // Must be power of 2
    static constexpr int16_t EMPTY_SLOT = -1;

private:
    struct StringMeta {
        uint16_t offset;
        uint16_t length;
    };

    // MEMORY LAYOUT
    uint16_t count_ = 0;           // Current number of keys
    uint16_t head_ = 0;            // Current write position in buffer
    StringMeta direct_[MAX_KEYS];  // Index -> String lookup
    int16_t lookup_[HASH_TABLE_SIZE]; // String Hash -> Index lookup
    char buffer_[BufferSize];      // The string heap

    // FNV-1a
    constexpr uint32_t hash_str(std::string_view s) const {
        uint32_t hash = 2166136261u;
        for (char c : s) {
            hash ^= static_cast<uint8_t>(c);
            hash *= 16777619u;
        }
        return hash;
    }

public:
    EmbeddedFlatMap() {
        std::fill(std::begin(lookup_), std::end(lookup_), EMPTY_SLOT);
        std::memset(direct_, 0, sizeof(direct_));
    }

	// 1. Adds the string to the map, returns its index (0-255)
    uint8_t add(std::string_view str) {
        if (count_ >= MAX_KEYS) {
            throw std::length_error("Max keys (256) exceeded");
        }
        if (head_ + str.size() > BufferSize) {
            throw std::length_error("String buffer overflow");
        }

        uint16_t current_offset = head_;
        std::memcpy(buffer_ + current_offset, str.data(), str.size());
        head_ += static_cast<uint16_t>(str.size());

        // Store Metadata
        uint8_t id = static_cast<uint8_t>(count_);
        direct_[id] = { current_offset, static_cast<uint16_t>(str.size()) };

        // Store Hash
        uint32_t h = hash_str(str);
        size_t idx = h & (HASH_TABLE_SIZE - 1); // Fast modulo

        // Linear Probing
        while (lookup_[idx] != EMPTY_SLOT) {
            // Does not check for duplicates
            idx = (idx + 1) & (HASH_TABLE_SIZE - 1);
        }
        lookup_[idx] = id;

        count_++;
        return id;
    }

    std::string_view get_string(uint8_t index) const {
        if (index >= count_) return {};
        const auto& meta = direct_[index];
        return std::string_view(buffer_ + meta.offset, meta.length);
    }

    // Returns the index of the string if present, else returns -1
    int16_t get_index(std::string_view key) const {
        uint32_t h = hash_str(key);
        size_t idx = h & (HASH_TABLE_SIZE - 1);

        // Linear Probing
        // We loop until we find the key OR we hit an empty slot
        for (size_t i = 0; i < HASH_TABLE_SIZE; ++i) {
            int16_t candidate_id = lookup_[idx];

            if (candidate_id == EMPTY_SLOT) {
                return -1; // Not found
            }

            // Verify the actual string matches
			// Maybe removed for performance later
            if (get_string(static_cast<uint8_t>(candidate_id)) == key) {
                return candidate_id;
            }

            idx = (idx + 1) & (HASH_TABLE_SIZE - 1);
        }
        return -1;
    }

    size_t size() const { return count_; }
};


template <size_t BufferSize = 2048>
class EmbeddedOneWayFlatMap {
public:
    static constexpr size_t MAX_KEYS = 256;

private:
    struct StringMeta {
        uint16_t offset;
        uint16_t length;
    };

    // MEMORY LAYOUT
    uint16_t count_ = 0;           // Current number of keys
    uint16_t head_ = 0;            // Current write position in buffer
    StringMeta direct_[MAX_KEYS];  // Index -> String lookup
    char buffer_[BufferSize];      // The string heap

public:
    EmbeddedOneWayFlatMap() {
        std::memset(direct_, 0, sizeof(direct_));
    }

    // 1. Adds the string to the map, returns its index (0-255)
    uint8_t add(std::string_view str) {
        if (count_ >= MAX_KEYS) {
            throw std::length_error("Max keys (256) exceeded");
        }
        if (head_ + str.size() > BufferSize) {
            throw std::length_error("String buffer overflow");
        }

        uint16_t current_offset = head_;
        std::memcpy(buffer_ + current_offset, str.data(), str.size());
        head_ += static_cast<uint16_t>(str.size());

        // Store Metadata
        uint8_t id = static_cast<uint8_t>(count_);
        direct_[id] = { current_offset, static_cast<uint16_t>(str.size()) };

        count_++;
        return id;
    }

    std::string_view get_string(uint8_t index) const {
        if (index >= count_) return {};
        const auto& meta = direct_[index];
        return std::string_view(buffer_ + meta.offset, meta.length);
    }

    size_t size() const { return count_; }
};