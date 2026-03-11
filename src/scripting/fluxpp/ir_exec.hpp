#pragma once

#include <queue>
#include <algorithm>
#include <Eigen/Dense>
#include <absl/container/flat_hash_set.h>
#include "fluxppParser.h"
#include "op_codes.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "../../data/ComputeFrame.hpp"

namespace scripting::fluxpp {
    /*
    63       56 55      48 47      36 35      24 23      12 11        0
    ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
    │  opcode  │  flags   │   dest   │  param3  │  param2  │  param1  │
    │  8 bits  │  8 bits  │ 12 bits  │ 12 bits  │ 12 bits  │ 12 bits  │
    └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
    opcode = [input type:3][op:5]
    000 - real
    001 - timestamp
    010 - bool
    011 - string
    100 - 111 reserved
    */

    static constexpr uint16_t MIN_ARG_INDEX = 0;
    static constexpr uint16_t TEMPORARY_RANGE_START = 1024;
    static constexpr uint16_t LITERAL_RANGE_START = 2048;
    static constexpr uint16_t MAX_ARG_INDEX = 4095;

    enum FLAG : uint8_t {
        NONE = 0,
        UNARY = 1,
        COMMUTATIVE = 2,
        TERNARY = 3,
        DEBUG = 0xF
    };

    enum INEQUALITY : uint8_t {
        LT = 0,
        LTE = 1,
        GT = 2,
        GTE = 3,
    };

    using IRLiteral = std::variant<double, int64_t>;

    struct alignas(8) Instruction {
        uint64_t instr;

        // Layout: [opcode:8][flags:8][dest:12][param3:12][param2:12][param1:12]
        static constexpr uint64_t MASK_12 = 0xFFF;

        Instruction(
            const uint8_t  opcode,
            const uint8_t  flags,
            const uint16_t dest,
            const uint16_t param3,
            const uint16_t param2,
            const uint16_t param1
        ) {
            instr =
                (static_cast<uint64_t>(opcode)        << 56) |
                (static_cast<uint64_t>(flags)          << 48) |
                (static_cast<uint64_t>(dest   & MASK_12) << 36) |
                (static_cast<uint64_t>(param3 & MASK_12) << 24) |
                (static_cast<uint64_t>(param2 & MASK_12) << 12) |
                (static_cast<uint64_t>(param1 & MASK_12));
        }

        uint8_t  get_opcode() const { return (instr >> 56) & 0xFF; }
        uint8_t  get_flags()  const { return (instr >> 48) & 0xFF; }
        uint16_t get_dest()   const { return (instr >> 36) & 0xFFF; }
        uint16_t get_param3() const { return (instr >> 24) & 0xFFF; }
        uint16_t get_param2() const { return (instr >> 12) & 0xFFF; }
        uint16_t get_param1() const { return (instr >>  0) & 0xFFF; }

        void set_dest  (uint16_t v) { instr = (instr & ~(MASK_12 << 36)) | ((static_cast<uint64_t>(v) & MASK_12) << 36); }
        void set_param3(uint16_t v) { instr = (instr & ~(MASK_12 << 24)) | ((static_cast<uint64_t>(v) & MASK_12) << 24); }
        void set_param2(uint16_t v) { instr = (instr & ~(MASK_12 << 12)) | ((static_cast<uint64_t>(v) & MASK_12) << 12); }
        void set_param1(uint16_t v) { instr = (instr & ~(MASK_12 <<  0)) | ((static_cast<uint64_t>(v) & MASK_12) <<  0); }

        void decompose(uint8_t& opcode, uint8_t& flags,
                       uint16_t& dest, uint16_t& param3,
                       uint16_t& param2, uint16_t& param1) const {
            opcode = get_opcode();
            flags  = get_flags();
            dest   = get_dest();
            param3 = get_param3();
            param2 = get_param2();
            param1 = get_param1();
        }
    };

    class Program {
    public:

        std::vector<Instruction> instructions_;
        std::vector<IRLiteral> literals_;
        std::vector<std::string> strings_;
        size_t memory_requirement_;

        Program(std::vector<Instruction> instructions, std::vector<IRLiteral> literals, std::vector<std::string> strings, const size_t mem_req)
            : instructions_(std::move(instructions)), literals_(std::move(literals)), strings_(std::move(strings)), memory_requirement_(mem_req) {}
    };

    class IRGenerator {
    public:
        IRGenerator() {
            free_temporaries.reserve(MAX_TEMPORARIES);
            for (uint16_t i = TEMPORARY_RANGE_START; i < MAX_TEMPORARIES; ++i) {
                free_temporaries.insert(i);
            }
        }

        [[nodiscard]] uint16_t AllocateTemporary() {
            if (free_temporaries.empty()) {
                // In a real implementation, we would handle register spilling here.
                throw std::runtime_error("No free registers available");
            }
            const auto it = free_temporaries.begin();
            const int16_t temp = *it;
            free_temporaries.erase(it);
            return temp;
        }

        void FreeTemporary(const uint16_t temp) {
            free_temporaries.insert(temp);
        }

        uint16_t RegisterLiteral(const IRLiteral temp) {
            const uint16_t literal_idx = literals.size();
            literals.push_back(temp);
            return static_cast<uint16_t>(literal_idx + LITERAL_RANGE_START);
        }

        // Retrieving string
        // Take operand (index into literal array)
        // This contains an index into the string array
        uint16_t RegisterStringLiteral(const std::string& str) {
            int64_t string_idx = static_cast<int64_t>(strings.size());
            const uint16_t literal_idx = literals.size();
            literals.push_back(string_idx);
            return static_cast<uint16_t>(literal_idx + LITERAL_RANGE_START);
        }

        void emit_add(const Type type, const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            if (type == Type::TREAL) {
                ir.emplace_back(OPCODE::ADD_R, FLAG::COMMUTATIVE, op1, op2, 0, dest);
            }
            else if (type == Type::TTIMESTAMP) {
                ir.emplace_back(OPCODE::ADD_T, FLAG::COMMUTATIVE, op1, op2, 0, dest);
            }
            else {
                throw std::runtime_error("Type does not support binary addition");
            }
        }

        void emit_sub(const Type type, const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            if (type == Type::TREAL) {
                ir.emplace_back(OPCODE::SUB_R, FLAG::COMMUTATIVE, op1, op2, 0, dest);
            }
            else if (type == Type::TTIMESTAMP) {
                ir.emplace_back(OPCODE::SUB_T, FLAG::COMMUTATIVE, op1, op2, 0, dest);
            }
            else {
                throw std::runtime_error("Type does not support binary subtraction");
            }
        }

        void emit_ieq(const Type type, const INEQUALITY ieq, const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            if (type == Type::TREAL) {
                switch (ieq) {
                    case LT:
                        ir.emplace_back(LT_R, NONE, op1, op2, 0, dest);
                        break;
                    case LTE:
                        ir.emplace_back(LTE_R, NONE, op1, op2, 0, dest);
                        break;
                    case GT:
                        ir.emplace_back(GT_R, NONE, op1, op2, 0, dest);
                        break;
                    case GTE:
                        ir.emplace_back(GTE_R, NONE, op1, op2, 0, dest);
                        break;
                }
            }
            else if (type == Type::TTIMESTAMP) {
                switch (ieq) {
                    case LT:
                        ir.emplace_back(LT_T, NONE, op1, op2, 0, dest);
                        break;
                    case LTE:
                        ir.emplace_back(LTE_T, NONE, op1, op2, 0, dest);
                        break;
                    case GT:
                        ir.emplace_back(GT_T, NONE, op1, op2, 0, dest);
                        break;
                    case GTE:
                        ir.emplace_back(GTE_T, NONE, op1, op2, 0, dest);
                        break;
                }
            }
            else {
                throw std::runtime_error("Type does not support binary less than");
            }
        }

        void emit_eq(const Type type, const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            switch (type) {
                case Type::TREAL:
                    ir.emplace_back(OPCODE::EQ_R, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TTIMESTAMP:
                    ir.emplace_back(OPCODE::EQ_T, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TBOOL:
                    ir.emplace_back(OPCODE::EQ_B, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TSTRING:
                    ir.emplace_back(OPCODE::EQ_S, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                default:
                    throw std::runtime_error("Type does not support binary equality");
            }
        }

        void emit_neq(const Type type, const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            switch (type) {
                case Type::TREAL:
                    ir.emplace_back(OPCODE::NEQ_R, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TTIMESTAMP:
                    ir.emplace_back(OPCODE::NEQ_T, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TBOOL:
                    ir.emplace_back(OPCODE::NEQ_B, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                case Type::TSTRING:
                    ir.emplace_back(OPCODE::NEQ_S, FLAG::COMMUTATIVE, op1, op2, 0, dest);
                    break;
                default:
                    throw std::runtime_error("Type does not support binary equality");
            }
        }

        void emit_mul(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(MUL_R, COMMUTATIVE, op1, op2, 0, dest);
        }
        void emit_div(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(DIV_R, NONE, op1, op2, 0, dest);
        }
        void emit_mod(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(MOD_R, NONE, op1, op2, 0, dest);
        }
        void emit_pow(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(POW_R, NONE, op1, op2, 0, dest);
        }
        void emit_neg(const uint16_t op1, const uint16_t dest) {
            ir.emplace_back(NEG_R, UNARY, op1, 0, 0, dest);
        }
        void emit_abs(const uint16_t op1, const uint16_t dest) {
            ir.emplace_back(ABS_R, UNARY, op1, 0, 0, dest);
        }
        void emit_and(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(AND_B, COMMUTATIVE, op1, op2, 0, dest);
        }
        void emit_or(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(OR_B, COMMUTATIVE, op1, op2, 0, dest);
        }
        void emit_xor(const uint16_t op1, const uint16_t op2, const uint16_t dest) {
            ir.emplace_back(XOR_B, COMMUTATIVE, op1, op2, 0, dest);
        }
        void emit_not(const uint16_t op1, const uint16_t dest) {
            ir.emplace_back(NOT_B, UNARY, op1, 0, 0, dest);
        }
        void emit_call(const uint16_t fn_idx, const uint16_t dest) {
            ir.emplace_back(CALL, NONE, fn_idx, 0, 0, dest);
        }
        void emit_load_scalar_arg(const uint16_t arg_idx, uint16_t load_idx) {
            ir.emplace_back(LDAS, NONE, arg_idx, load_idx, 0, 0);
        }
        void emit_load_vector_arg(const uint16_t arg_idx, uint16_t load_idx) {
            ir.emplace_back(LDAV, NONE, arg_idx, load_idx, 0, 0);
        }
        void emit_copy(const uint16_t src_idx, const uint16_t dest_idx) {
            ir.emplace_back(COPY, NONE, src_idx, 0, 0, dest_idx);
        }
        void emit_zero_out(const uint16_t src_idx) {
            ir.emplace_back(ZERO, NONE, src_idx, 0, 0, 0);
        }
        void emit_filter(const uint16_t target_col_idx, const uint16_t cond_expr_idx) {
            ir.emplace_back(FILTER, NONE, cond_expr_idx, 0, 0, target_col_idx);
        }
        void emit_drop(const uint16_t target_col_idx) {
            ir.emplace_back(DROP, NONE, target_col_idx, 0, 0, 0);
        }
        void emit_clamp(const uint16_t target_col_idx, const uint16_t lower_bd, const uint16_t upper_bd) {
            ir.emplace_back(CLAMP, NONE, lower_bd, upper_bd, 0, target_col_idx);
        }
        void emit_create(const uint16_t string_idx, const uint16_t expr_idx) {
            ir.emplace_back(CREATE, NONE, expr_idx, 0, 0, string_idx);
        }
        void emit_fill(const uint16_t target_col_idx, const uint16_t literal_idx) {
            ir.emplace_back(FILL, NONE, literal_idx, 0, 0, target_col_idx);
        }
        void emit_assert(const uint16_t expr_idx) {
            ir.emplace_back(ASSERT, NONE, expr_idx, 0, 0, 0);
        }
        void emit_end() {
            ir.emplace_back(END, NONE, 0, 0, 0, 0);
        }

        Program GetProgram() {
            auto intervals = compute_intervals();
            linear_scan(intervals);
            return Program(ir, literals, strings, mem_req);
        }
    private:
        absl::flat_hash_set<int16_t> free_temporaries;
        std::vector<Instruction> ir;
        std::vector<IRLiteral> literals;
        std::vector<std::string> strings;
        size_t mem_req = 0;
        static constexpr uint16_t MAX_TEMPORARIES = 256;

        struct Interval {
            uint16_t virtual_tmp;
            uint32_t def;
            uint32_t last_use;
        };

        struct Allocation {
            uint16_t virtual_tmp;
            uint16_t physical_slot;
        };

        std::vector<Interval> compute_intervals() const {
            std::unordered_map<uint16_t, Interval> intervals;
            auto is_temp = [](const uint16_t idx) {
                return idx >= TEMPORARY_RANGE_START && idx < LITERAL_RANGE_START;
            };

            for (uint16_t i = 0; i < ir.size(); i++) {
                auto& instr = ir[i];
                const auto dest = instr.get_dest();
                if (is_temp(dest)) {
                    intervals[dest].virtual_tmp = dest;
                    intervals[dest].def = i;
                }

                const bool unary = instr.get_flags() & UNARY;
                const bool ternary = instr.get_flags() & TERNARY;
                if (is_temp(instr.get_param1())) {
                    const auto p1 = instr.get_param1();
                    intervals[p1].last_use = i;
                }
                if (!unary && is_temp(instr.get_param2())) {
                    const auto p2 = instr.get_param2();
                    intervals[p2].last_use = i;
                }
                if (ternary && is_temp(instr.get_param3())) {
                    const auto p3 = instr.get_param3();
                    intervals[p3].last_use = i;
                }
            }

            std::vector<Interval> result;
            for (auto &iv: intervals | std::views::values) result.push_back(iv);
            return result;
        }

        void linear_scan(std::vector<Interval>& intervals) {
            // Sort by definition point
            std::ranges::sort(intervals, [](auto& a, auto& b) { return a.def < b.def; });

            // Active set: sorted by last_use (min-heap)
            auto cmp = [](const Interval* a, const Interval* b) {
                return a->last_use > b->last_use; // min-heap on last_use
            };
            std::priority_queue<const Interval*,
                std::vector<const Interval*>,
                decltype(cmp)> active(cmp);

            // Free slot pool
            std::priority_queue<uint16_t,
                                std::vector<uint16_t>,
                                std::greater<uint16_t>> free_slots; // min-heap, lowest first
            uint16_t next_new_slot = 0;

            std::vector<Allocation> result;
            std::unordered_map<uint16_t, uint16_t> virt_to_phys;

            auto alloc_slot = [&]() -> uint16_t {
                if (!free_slots.empty()) {
                    uint16_t s = free_slots.top();
                    free_slots.pop();
                    return s;
                }
                return next_new_slot++;
            };

            for (auto& iv : intervals) {
                // Expire intervals that ended before this one starts
                while (!active.empty() && active.top()->last_use < iv.def) {
                    free_slots.push(virt_to_phys[active.top()->virtual_tmp]);
                    active.pop();
                }

                const uint16_t slot = alloc_slot();
                virt_to_phys[iv.virtual_tmp] = slot;
                result.push_back({iv.virtual_tmp, slot});
                active.push(&iv);
            }

            // next_new_slot is now your total physical temporary count
            // return result;
            mem_req = next_new_slot;

            auto remap = [&](const uint16_t idx) -> uint16_t {
                const auto it = virt_to_phys.find(idx);
                return (it != virt_to_phys.end()) ? (it->second + TEMPORARY_RANGE_START) : idx;
                // re-offset back into the temporary range after remapping
            };

            for (auto& instr : ir) {
                instr.set_dest(remap(instr.get_dest()));
                instr.set_param1(remap(instr.get_param1()));
                const auto flags = instr.get_flags();
                if (!(flags & UNARY))
                    instr.set_param2(remap(instr.get_param2()));
                if (!(flags & TERNARY))
                    instr.set_param3(remap(instr.get_param3()));
            }

        }
    };

    class IRExec {
        using Block = std::vector<double, Eigen::aligned_allocator<double>>;
    public:
        explicit IRExec(Program&& prog, const size_t n_rows, std::shared_ptr<df::DataFrame> df) : program(std::move(prog)), n_rows(n_rows), df_(std::move(df)) {}
        void Initialize() {
            memory = Block(program.memory_requirement_ * n_rows);
        }
        void Execute() {
            size_t iptr = 0;
            while (true) {
                const Instruction& inst = program.instructions_[iptr];
                const uint8_t opcode = inst.get_opcode();
                if (opcode == END)
                    break;
                if (opcode == NOP)
                    continue;

                ++iptr;
            }
        }
    private:
        Program program;
        size_t n_rows;
        std::shared_ptr<df::DataFrame> df_;
        Block memory;
        ArgArray args = {};
        VectorArgArray argv = {};
    };

}
