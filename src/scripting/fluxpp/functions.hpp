#pragma once

#include <array>
#include <cstdint>
#include <EigenDefinitions.hpp>
#include <unordered_map>
#include <variant>
#include "GlobalRandomEngine.hpp"
#include "types.hpp"

namespace scripting::fluxpp {
    //template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
    //template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

    using ArgArray = std::array<double, 4>;
    using VectorArgArray = std::array<EigenColDoubleVec, 4>;

    enum FNT : uint8_t {
        PASS,
        REDUCE,
        EXPAND
    };

    struct alignas(16) FN_DATA {
        uint64_t index;
        Type arg_type;
        bool supports_vectors;
        bool supports_scalars;
        uint8_t arg_count;
        FNT fnt;
    };

    static std::unordered_map<std::string, FN_DATA> fn_index_map = {
        // 1. SCALAR ARGS TO SCALR RETURNS
        // --- 1 Argument ---
        {"abs", {0, Type::TREAL, true, true, 1, PASS }},
        {"sign", {1, Type::TREAL, true, true, 1, PASS }},
        {"sin", {2, Type::TREAL, true, true, 1, PASS }},
        {"cos", {3, Type::TREAL, true, true, 1, PASS }},
        {"tan", {4, Type::TREAL, true, true, 1, PASS }},
        {"asin", {5, Type::TREAL, true, true, 1, PASS }},
        {"acos", {6, Type::TREAL, true, true, 1, PASS }},
        {"atan", {7, Type::TREAL, true, true, 1, PASS }},
        {"sinh", {8, Type::TREAL, true, true, 1, PASS }},
        {"cosh", {9, Type::TREAL, true, true, 1, PASS }},
        {"tanh", {10, Type::TREAL, true, true, 1, PASS }},
        {"asinh", {11, Type::TREAL, true, true, 1, PASS }},
        {"acosh", {12, Type::TREAL, true, true, 1, PASS }},
        {"atanh", {13, Type::TREAL, true, true, 1, PASS }},
        {"exp", {14, Type::TREAL, true, true, 1, PASS }},
        {"exp2", {15, Type::TREAL, true, true, 1, PASS }},
        {"expm1", {16, Type::TREAL, true, true, 1, PASS }},
        {"log", {17, Type::TREAL, true, true, 1, PASS }},
        {"ln", {18, Type::TREAL, true, true, 1, PASS }},
        {"log10", {19, Type::TREAL, true, true, 1, PASS }},
        {"log2", {20, Type::TREAL, true, true, 1, PASS }},
        {"sqrt", {21, Type::TREAL, true, true, 1, PASS }},
        {"cbrt", {22, Type::TREAL, true, true, 1, PASS }},
        {"floor", {23, Type::TREAL, true, true, 1, PASS }},
        {"ceil", {24, Type::TREAL, true, true, 1, PASS }},
        {"trunc", {25, Type::TREAL, true, true, 1, PASS }},
        {"round", {26, Type::TREAL, true, true, 1, PASS }},
        {"rint", {27, Type::TREAL, true, true, 1, PASS }},
        {"erf", {28, Type::TREAL, true, true, 1, PASS }},
        {"erfc", {29, Type::TREAL, true, true, 1, PASS }},
        {"tgamma", {30, Type::TREAL, true, true, 1, PASS }},
        {"lgamma", {31, Type::TREAL, true, true, 1, PASS }},

        // --- 2 Arguments ---
        {"pow", {32, Type::TREAL, true, true, 2, PASS }},    // (base, exponent)
        {"atan2", {33, Type::TREAL, true, true, 2, PASS }},  // (y, x)
        {"hypot", {34, Type::TREAL, true, true, 2, PASS }},  // (x, y)
        {"fmod", {35, Type::TREAL, true, true, 2, PASS }},   // (x, y)

        // --- 4 Arguments ---
        {"fv", {36, Type::TREAL, true, true, 4, PASS }},     // (rate, nper, pmt, pv)
        {"pv", {37, Type::TREAL, true, true, 4, PASS }},     // (rate, nper, pmt, fv)
        {"pmt", {38, Type::TREAL, true, true, 4, PASS }},    // (rate, nper, pv, fv)
        {"nper", {39, Type::TREAL, true, true, 4, PASS }},   // (rate, pmt, pv, fv)

        // 2. SCALAR ARGS TO VECTOR RETURNS
        // --- 2 Arguments ---
        {"exponential", {400, Type::TREAL, false, true, 1, EXPAND }}, // (lambda/scale, size_of_vector)

        // --- 3 Arguments ---
        {"normal", {401, Type::TREAL, false, true, 2, EXPAND }},      // (mean, stddev, size_of_vector)
        {"uniform", {402, Type::TREAL, false, true, 2, EXPAND }},     // (min, max, size_of_vector)
        //{"linspace", 42},    // (start, stop, num_points)

        // 3. VECTOR ARGS TO SCALAR RETURNS
        // --- 1 Argument (Takes 1 Vector) ---
        {"sum", {160, Type::TREAL, true, false, 1, REDUCE }},
        {"mean", {161, Type::TREAL, true, false, 1, REDUCE }},
        {"min", {162, Type::TREAL, true, false, 1, REDUCE }},
        {"max", {163, Type::TREAL, true, false, 1, REDUCE }},
        {"count", {164, Type::TREAL, true, false, 1, REDUCE }},
        {"count_distinct", {165, Type::TREAL, true, false, 1, REDUCE }},
        {"stddev", {166, Type::TREAL, true, false, 1, REDUCE }},
        {"variance", {167, Type::TREAL, true, false, 1, REDUCE }},
        {"skew", {168, Type::TREAL, true, false, 1, REDUCE }},
        {"kurtosis", {169, Type::TREAL, true, false, 1, REDUCE }},
        {"mode", {170, Type::TREAL, true, false, 1, REDUCE }},
        {"product", {171, Type::TREAL, true, false, 1, REDUCE }},
        {"norm", {172, Type::TREAL, true, false, 1, REDUCE }},        // Vector magnitude
        {"irr", {173, Type::TREAL, true, false, 1, REDUCE }},         // Internal Rate of Return (takes a vector of cash flows)

        // --- 2 Arguments (Takes 2 Vectors, or 1 Scalar + 1 Vector) ---
        {"dot", {174, Type::TREAL, true, false, 2, REDUCE }},         // Dot product (vec1, vec2)
        {"npv", {175, Type::TREAL, true, false, 2, REDUCE }},         // Net Present Value (discount_rate_scalar, cash_flows_vector)

        // 4. VECTOR ARGS TO VECTOR RETURNS
        // --- 1 Argument (Takes 1 Vector) ---
        {"cumsum", {200, Type::TREAL, true, false, 1, EXPAND }},      // Cumulative sum
        {"cumprod", {201, Type::TREAL, true, false, 1, EXPAND }},     // Cumulative product
        {"diff", {202, Type::TREAL, true, false, 1, EXPAND }},        // Discrete difference
        {"normalize", {203, Type::TREAL, true, false, 1, EXPAND }},   // Scales vector to unit length

        // Date and Time functions
        {"year", {50, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"day_of_year", {51, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"month", {52, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"day", {53, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"day_of_week", {54, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"week_of_year", {55, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"hour", {56, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"minute", {57, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"second", {58, Type::TTIMESTAMP, true, true, 1, PASS }},
        {"second_of_day", {59, Type::TTIMESTAMP, true, true, 1, PASS }},
    };
    enum class FN_ORDER {
        SCALAR_SCALAR,
        SCALAR_VECTOR,
        VECTOR_SCALAR,
        VECTOR_VECTOR,
    };

    FN_ORDER get_fn_order(const uint64_t index);
    bool is_aggregated(const uint64_t index);

    FN_DATA get_fn_index(const std::string &fn);

    // Implicit constant functions
    double resolve_scalar_function_scalar(const ArgArray& args, const uint64_t index);

    // Implicitly trained aggregates
    double resolve_scalar_function_vector(const VectorArgArray& args, const uint64_t index, const uint32_t ndims);

    // In place compute
    EigenColDoubleVec resolve_vector_function_scalar(const ArgArray& args, const uint32_t index, const uint32_t ndims);

    // In place compute. These cannot be trained
    EigenColDoubleVec resolve_vector_function_vector(const VectorArgArray& args, const uint32_t index, const uint32_t ndims);

}
