#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <ranges>
#include <unordered_map>
#include <vector>


static constexpr uint32_t kTemporaryThreshold = 16384u;

struct VirtualStorage {
    uint32_t index{};
    uint32_t tag{};       // RowTag: changes at every row-altering operation

    // A VS is a compiler temporary if its index is below the threshold.
    // Indices >= kTemporaryThreshold are named inputs / outputs and are
    // not touched by the allocator.
    [[nodiscard]] bool is_temporary() const noexcept {
        return index < kTemporaryThreshold;
    }

    bool operator==(const VirtualStorage&) const noexcept = default;
};

struct VirtualStorageHash {
    std::size_t operator()(const VirtualStorage& vs) const noexcept {
        // Pack tag into the high 32 bits and index into the low 32 bits.
        return std::hash<uint64_t>{}(
            static_cast<uint64_t>(vs.tag) << 32u | vs.index);
    }
};

// Base class for a single lowered operation.
// operands: all input VirtualStorages consumed by this op.
// destination: the single output VirtualStorage produced by this op.
class IROP {
public:
    std::vector<VirtualStorage> operands;
    VirtualStorage              destination;
    virtual ~IROP() = default;
};

// -----------------------------------------------------------------------------
// Allocation result
// -----------------------------------------------------------------------------

// Maps every temporary VirtualStorage to a physical slot index within its
// tag group.  Two temporaries with different tags are always in separate
// pools and their slot indices are independent.
//
// peak_slots[tag] gives the number of pool slots needed for that tag group,
// i.e. the exact buffer count to pre-allocate per RowTag epoch.
struct AllocationResult {
    std::unordered_map<VirtualStorage, uint32_t, VirtualStorageHash>
        slot_map;

    std::unordered_map<uint32_t /*tag*/, uint32_t /*slot count*/>
        peak_slots;
};

// -----------------------------------------------------------------------------
// Register allocation
// -----------------------------------------------------------------------------

// Performs liveness analysis followed by linear-scan register allocation over
// the SSA-form op sequence.
//
// Constraints enforced:
//   1. Only temporaries (VS::is_temporary()) are allocated.
//   2. Two temporaries may share a physical slot only when they carry the same
//      tag, i.e. they belong to the same row-size epoch.
//   3. Two temporaries sharing a slot must have non-overlapping live intervals.
//
// The ops vector is assumed to be in topological (execution) order so that
// every operand VS has been defined by an earlier instruction — standard SSA.
[[nodiscard]] inline AllocationResult allocate_registers(
    const std::vector<IROP*>& ops)
{
    // ------------------------------------------------------------------
    // Phase 1 — Liveness analysis
    //
    // For each temporary VS build a half-open live interval [def, last_use].
    // def_point  : index of the instruction that defines (writes) the VS.
    // last_use   : index of the last instruction that reads the VS as an
    //              operand.  Initialised to def_point so that a VS with no
    //              uses still occupies a slot for the cycle it is defined.
    // ------------------------------------------------------------------

    struct Interval {
        VirtualStorage vs;
        uint32_t       def_point{};
        uint32_t       last_use{};
    };

    std::unordered_map<VirtualStorage, Interval, VirtualStorageHash>
        interval_map;

    const auto n = static_cast<uint32_t>(ops.size());

    for (uint32_t i = 0; i < n; ++i) {
        const IROP& op = *ops[i];

        // Record the definition.
        if (op.destination.is_temporary()) {
            auto& iv     = interval_map[op.destination];
            iv.vs        = op.destination;
            iv.def_point = i;
            iv.last_use  = i;   // minimum live range: the def itself
        }

        // Extend last_use for each operand that is a temporary.
        for (const VirtualStorage& src : op.operands) {
            if (!src.is_temporary()) continue;
            if (auto it = interval_map.find(src); it != interval_map.end())
                it->second.last_use = std::max(it->second.last_use, i);
        }
    }

    // ------------------------------------------------------------------
    // Phase 2 — Partition intervals by RowTag
    //
    // Slots are never shared across tag boundaries because different tags
    // represent vectors of different (or unknown-until-runtime) row counts.
    // Filter outputs are bounded above by the input size so they round up
    // to the parent tag's slot size.  Append outputs mint a new tag and
    // land in their own dynamic slab — handled by the caller; the allocator
    // simply assigns slot indices independently per tag.
    // ------------------------------------------------------------------

    std::unordered_map<uint32_t, std::vector<Interval>> by_tag;
    by_tag.reserve(interval_map.size());

    for (auto &iv: interval_map | std::views::values)
        by_tag[iv.vs.tag].push_back(iv);

    // ------------------------------------------------------------------
    // Phase 3 — Linear-scan allocation per tag group
    //
    // Standard linear-scan with a free-list for slot recycling.  Intervals
    // are processed in order of def_point.  An active set sorted by last_use
    // lets us expire finished intervals in O(k) per step where k is the
    // number of intervals expiring.
    //
    // next_slot monotonically grows only when the free-list is empty, so it
    // counts the peak simultaneously-live slots — exactly the pool depth
    // required for this tag group.
    // ------------------------------------------------------------------

    AllocationResult result;

    for (auto& [tag, intervals] : by_tag) {

        // Sort by start point so we process intervals left-to-right.
        std::ranges::sort(intervals, {}, &Interval::def_point);

        std::vector<uint32_t> free_slots;   // recycled slot indices
        uint32_t              next_slot = 0u;

        // Active set: intervals that have been assigned a slot and are
        // still live.  Kept sorted ascending by last_use so the front
        // element is always the first to expire.
        struct ActiveEntry {
            uint32_t last_use;
            uint32_t slot;
            // For std::ranges::lower_bound on last_use.
            bool operator<(const ActiveEntry& o) const noexcept {
                return last_use < o.last_use;
            }
        };
        std::vector<ActiveEntry> active;

        for (const Interval& iv : intervals) {

            // --- Expiry pass -------------------------------------------
            // Any active interval whose last_use is strictly before the
            // current def_point has gone cold; release its slot.  Because
            // active is sorted by last_use the expired entries are a prefix.
            {
                /*auto first_live = std::ranges::lower_bound(
                    active,
                    ActiveEntry{iv.def_point, 0u});*/
                auto first_live = std::ranges::lower_bound(active,iv.def_point, std::less{}, &ActiveEntry::last_use);

                for (auto it = active.begin(); it != first_live; ++it)
                    free_slots.push_back(it->slot);

                active.erase(active.begin(), first_live);
            }

            // --- Slot assignment ---------------------------------------
            // Prefer a recycled slot; mint a new one only if the free-list
            // is empty.
            const uint32_t slot = [&] {
                if (!free_slots.empty()) {
                    const uint32_t s = free_slots.back();
                    free_slots.pop_back();
                    return s;
                }
                return next_slot++;
            }();

            result.slot_map[iv.vs] = slot;

            // Insert into active maintaining sort order by last_use.
            const ActiveEntry entry{iv.last_use, slot};
            active.insert(std::ranges::lower_bound(active, entry), entry);
        }

        // next_slot == peak simultaneously-live count for this tag group.
        result.peak_slots[tag] = next_slot;
    }

    return result;
}