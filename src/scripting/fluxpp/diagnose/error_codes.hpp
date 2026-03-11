#pragma once
// ============================================================
//  FluxPP — ErrorCodes.h
//  Single source of truth for every diagnostic code.
//
//  Naming convention:
//    [Severity_]<CATEGORY><NNN>_<SCREAMING_SNAKE>
//
//  Categories
//    SSA  – immutability / single-static-assignment violations
//    REF  – identifier resolution failures
//    TYP  – type mismatches / unsupported types
//    DIM  – scalar-vs-vector dimensionality violations
//    ARG  – function-call argument errors
//    RNG  – value-range / domain errors
//    SEM  – whole-statement semantic errors
//    RUN  – runtime-only errors (IR generator)
//    W_*  – warnings (any category prefix)
// ============================================================

#include <array>
#include <cassert>
#include <cstdint>
#include <string_view>

namespace scripting::fluxpp {

// Numeric codes
// Ranges:   0000- 999  SYN
//           1000-1999  SSA
//           2000-2999  REF
//           3000-3999  TYP
//           4000-4999  DIM
//           5000-5999  ARG
//           6000-6999  RNG
//           7000-7999  SEM
//           8000-8999  RUN
//           9000-9999  Warnings (W_*)

enum class ErrorCode : uint32_t {

    // ── Syntax Errors ────────────────────────────────────── 0xxx
    SYN001_SYNTAX_ERROR                 = 0001,
    SYN002_MISMATCHED_TOKEN             = 0002,
    SYN003_NO_VIABLE_ALTERNATIVE        = 0003,
    SYN004_EARLY_EXIT                   = 0004,
    SYN005_FAILED_PREDICATE             = 0005,

    // ── SSA / Immutability ────────────────────────────────────── 1xxx
    SSA001_IMMUTABLE_REASSIGNMENT       = 1001,
    // LET x = … then LET x = …  (or SET x = … on a LET variable)

    SSA002_LET_SHADOWS_COLUMN           = 1002,
    // LET x = … where x is already a data frame column

    // ── Reference / Scope ─────────────────────────────────────── 2xxx
    REF001_CREATE_SHADOWS_VARIABLE      = 2001,
    // CREATE x AS … where x is already a LET variable

    REF002_CREATE_DUPLICATE_COLUMN      = 2002,
    // CREATE x AS … where x already exists as a column

    REF003_UNKNOWN_COLUMN               = 2003,
    // SET / FILL / CLAMP / REMOVE references a column that does not exist

    REF004_UNKNOWN_VARIABLE_OR_COLUMN   = 2004,
    // An expression references an identifier that is neither a variable nor a column

    REF005_RENAME_SRC_NOT_FOUND         = 2005,
    // RENAME x TO y — x does not exist in the data frame

    REF006_RENAME_DST_CONFLICT          = 2006,
    // RENAME x TO y — y is already a variable or column

    REF007_UNKNOWN_FUNCTION             = 2007,
    // Call to an undeclared function ID(…)

    REF008_SHADOWS_VARIABLE             = 2008,

    // ── Type ──────────────────────────────────────────────────── 3xxx
    TYP001_TYPE_MISMATCH                = 3001,
    // Generic: two sub-expressions must share a type but do not

    TYP002_UNSUPPORTED_TYPE_FOR_OP      = 3002,
    // Operator does not support the operand type (e.g. ABS on bool)

    TYP003_CONDITION_NOT_BOOL           = 3003,
    // KEEP IF / DROP IF / ASSERT / REMOVE IF / ternary cond is not bool

    TYP004_TERNARY_BRANCH_MISMATCH      = 3004,
    // true_expr and false_expr of ternary evaluate to different types

    TYP005_CLAMP_BOUNDS_TYPE_MISMATCH   = 3005,
    // from and to of CLAMP evaluate to different types

    TYP006_CLAMP_BOUND_UNSUPPORTED_TYPE = 3006,
    // CLAMP bound is not real or timestamp

    TYP007_SET_TYPE_MISMATCH            = 3007,
    // SET col = expr — expr type differs from column type

    TYP008_FILL_TYPE_MISMATCH           = 3008,
    // FILL col WITH expr — expr type differs from column type

    TYP009_FUNC_ARG_TYPE_MISMATCH       = 3009,
    // Argument type does not match the function's expected parameter type

    TYP010_FUNC_ARGS_HETEROGENEOUS      = 3010,
    // Function requires all args to share a type; heterogeneous args supplied

    TYP011_COMPARISON_TYPE_MISMATCH     = 3011,
    // Both sides of == / != / < / > … must share a type

    TYP012_INEQUALITY_UNSUPPORTED_TYPE  = 3012,
    // < / <= / > / >= only support real and timestamp

    TYP013_ARITHMETIC_TYPE_MISMATCH     = 3013,
    // Both sides of +/-/*/÷/% must share a type

    TYP014_ARITHMETIC_UNSUPPORTED_TYPE  = 3014,
    // Arithmetic on an unsupported type (e.g. bool + bool)

    TYP015_LOGICAL_OPERAND_NOT_BOOL     = 3015,
    // AND / OR / NOT applied to a non-bool expression

    TYP016_NEGATION_NOT_REAL            = 3016,
    // Unary minus applied to a non-real expression

    TYP017_ABS_NOT_REAL                 = 3017,
    // ABS(expr) where expr is not real

    // ── Dimensionality ────────────────────────────────────────── 4xxx
    DIM001_EXPECTED_VECTOR_GOT_SCALAR   = 4001,
    // KEEP IF / DROP IF requires a vector mask; scalar expression supplied

    DIM002_EXPECTED_SCALAR_GOT_VECTOR   = 4002,
    // Statement / operator requires scalar; vector expression supplied

    DIM003_FUNC_ARG_DIM_MISMATCH        = 4003,
    // Function parameter expects a specific dimensionality; wrong supplied

    DIM004_TERNARY_DIM_MISMATCH         = 4004,
    // All three ternary sub-expressions must be scalars or all vectors; mixed

    // ── Arguments ─────────────────────────────────────────────── 5xxx
    ARG001_WRONG_ARG_COUNT              = 5001,
    // Call site provides N args; function expects M

    // ── Range / Domain ────────────────────────────────────────── 6xxx
    RNG001_CLAMP_EMPTY_RANGE            = 6001,
    // CLAMP: (to - from) <= 0, making the range empty or inverted

    // ── Semantic (whole-statement) ────────────────────────────── 7xxx
    SEM001_ASSERT_FAILED                = 7001,
    // ASSERT expr — expr evaluated to false at runtime

    SEM002_ISOLATED_EXPRESSION          = 7002,
    // <expr> statements are only allowed in specific contexts

    // ── Runtime (IR generator / interpreter) ──────────────────── 8xxx
    RUN001_DIVISION_BY_ZERO             = 8001,
    // Division or modulo by a zero-valued expression at runtime

    RUN002_FILTER_ALL_FALSE             = 8002,
    // KEEP IF — mask is all-false; resulting data frame would be empty

    RUN003_DROP_ALL_TRUE                = 8003,
    // DROP IF — mask is all-true; resulting data frame would be empty

    RUN004_IMPLICIT_CAST_FAILURE        = 8004,
    // CREATE produced a column whose element type required an implicit cast
    // that could not be completed for at least one element

    // ── Warnings ──────────────────────────────────────────────── 9xxx
    W_SEM001_REMOVE_ALL_COLUMNS         = 9001,
    // REMOVE will drop every column, leaving an empty data frame

    W_TYP001_IMPLICIT_CAST              = 9002,
    // CREATE / SET produces a column whose declared type differs from the
    // expression type; an implicit cast will be applied at runtime

    W_SEM002_CREATE_SCALAR_BROADCAST    = 9003,
    // CREATE col AS <scalar_expr> — scalar will be broadcast to column length

    W_SEM003_SET_SCALAR_BROADCAST       = 9004,
    // SET col = <scalar_expr> — scalar will be broadcast to column length
};

enum class Severity : uint8_t {
    Error,
    Warning,
};

struct ErrorMeta {
    ErrorCode        code;
    Severity         severity;
    std::string_view tag;       // "SSA001", printed in brackets
    std::string_view title;     // concise human-readable title (≤ ~60 chars)
};

class KMap {
    public:
    static KMap& GetInstance() {
        static KMap instance;
        return instance;
    }

    // Returns the ErrorMeta for a given code.
    // Terminates (std::abort) if the code is not registered — that is a
    // programming error, not a user error.
    [[nodiscard]] static const ErrorMeta& GetMeta(const ErrorCode code) noexcept {
        for (const auto& m : kMetaTable) {
            if (m.code == code) return m;
        }
        // Unregistered code — programming error.
        assert(false && "fluxpp::getMeta: unregistered ErrorCode");
        std::abort();
    }
private:
    constexpr static std::array<ErrorMeta, 48> kMetaTable {{

    // SYN
    { ErrorCode::SYN001_SYNTAX_ERROR,                 Severity::Error,   "SYN001", "Syntax Error"},
    { ErrorCode::SYN002_MISMATCHED_TOKEN,             Severity::Error,   "SYN002", "Mismatched Token"},
    { ErrorCode::SYN003_NO_VIABLE_ALTERNATIVE,        Severity::Error,   "SYN003", "No viable alternative"},
    { ErrorCode::SYN004_EARLY_EXIT,                   Severity::Error,   "SYN004", "Parser early exit"},
    { ErrorCode::SYN005_FAILED_PREDICATE,             Severity::Error,   "SYN005", "Failed predicate while parsing"},

    // SSA
    { ErrorCode::SSA001_IMMUTABLE_REASSIGNMENT,       Severity::Error,   "SSA001", "Reassignment to immutable variable"             },
    { ErrorCode::SSA002_LET_SHADOWS_COLUMN,           Severity::Error,   "SSA002", "LET variable name conflicts with existing column"},

    // REF
    { ErrorCode::REF001_CREATE_SHADOWS_VARIABLE,      Severity::Error,   "REF001", "CREATE identifier already declared as variable"  },
    { ErrorCode::REF002_CREATE_DUPLICATE_COLUMN,      Severity::Error,   "REF002", "CREATE identifier already exists as column"      },
    { ErrorCode::REF003_UNKNOWN_COLUMN,               Severity::Error,   "REF003", "Reference to undeclared column"                  },
    { ErrorCode::REF004_UNKNOWN_VARIABLE_OR_COLUMN,   Severity::Error,   "REF004", "Reference to undeclared identifier"              },
    { ErrorCode::REF005_RENAME_SRC_NOT_FOUND,         Severity::Error,   "REF005", "RENAME source column does not exist"             },
    { ErrorCode::REF006_RENAME_DST_CONFLICT,          Severity::Error,   "REF006", "RENAME destination name already in use"          },
    { ErrorCode::REF007_UNKNOWN_FUNCTION,             Severity::Error,   "REF007", "Call to undeclared function"                     },
    { ErrorCode::REF008_SHADOWS_VARIABLE,             Severity::Error,   "REF008", "Identifier shadows a variable"                   },

    // TYP
    { ErrorCode::TYP001_TYPE_MISMATCH,                Severity::Error,   "TYP001", "Type mismatch between operands"                  },
    { ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP,      Severity::Error,   "TYP002", "Operator does not support this operand type"     },
    { ErrorCode::TYP003_CONDITION_NOT_BOOL,           Severity::Error,   "TYP003", "Condition expression must evaluate to bool"      },
    { ErrorCode::TYP004_TERNARY_BRANCH_MISMATCH,      Severity::Error,   "TYP004", "Ternary branches evaluate to different types"    },
    { ErrorCode::TYP005_CLAMP_BOUNDS_TYPE_MISMATCH,   Severity::Error,   "TYP005", "CLAMP 'from' and 'to' bounds have different types"},
    { ErrorCode::TYP006_CLAMP_BOUND_UNSUPPORTED_TYPE, Severity::Error,   "TYP006", "CLAMP bound must be real or timestamp"           },
    { ErrorCode::TYP007_SET_TYPE_MISMATCH,            Severity::Error,   "TYP007", "SET expression type differs from column type"    },
    { ErrorCode::TYP008_FILL_TYPE_MISMATCH,           Severity::Error,   "TYP008", "FILL expression type differs from column type"   },
    { ErrorCode::TYP009_FUNC_ARG_TYPE_MISMATCH,       Severity::Error,   "TYP009", "Function argument type mismatch"                 },
    { ErrorCode::TYP010_FUNC_ARGS_HETEROGENEOUS,      Severity::Error,   "TYP010", "Function arguments must share the same type"     },
    { ErrorCode::TYP011_COMPARISON_TYPE_MISMATCH,     Severity::Error,   "TYP011", "Comparison operands have different types"        },
    { ErrorCode::TYP012_INEQUALITY_UNSUPPORTED_TYPE,  Severity::Error,   "TYP012", "Inequality operator requires real or timestamp"  },
    { ErrorCode::TYP013_ARITHMETIC_TYPE_MISMATCH,     Severity::Error,   "TYP013", "Arithmetic operands have different types"        },
    { ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE,  Severity::Error,   "TYP014", "Operator does not support this arithmetic type"  },
    { ErrorCode::TYP015_LOGICAL_OPERAND_NOT_BOOL,     Severity::Error,   "TYP015", "Logical operator requires bool operands"         },
    { ErrorCode::TYP016_NEGATION_NOT_REAL,            Severity::Error,   "TYP016", "Unary negation requires a real operand"          },
    { ErrorCode::TYP017_ABS_NOT_REAL,                 Severity::Error,   "TYP017", "ABS requires a real operand"                     },

    // DIM
    { ErrorCode::DIM001_EXPECTED_VECTOR_GOT_SCALAR,   Severity::Error,   "DIM001", "Expected vector expression, got scalar"          },
    { ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR,   Severity::Error,   "DIM002", "Expected scalar expression, got vector"          },
    { ErrorCode::DIM003_FUNC_ARG_DIM_MISMATCH,        Severity::Error,   "DIM003", "Function argument has wrong dimensionality"      },
    { ErrorCode::DIM004_TERNARY_DIM_MISMATCH,         Severity::Error,   "DIM004", "Ternary sub-expressions have mixed dimensionality"},

    // ARG
    { ErrorCode::ARG001_WRONG_ARG_COUNT,              Severity::Error,   "ARG001", "Wrong number of arguments in function call"      },

    // RNG
    { ErrorCode::RNG001_CLAMP_EMPTY_RANGE,            Severity::Error,   "RNG001", "CLAMP range is empty or inverted (to <= from)"   },

    // SEM
    { ErrorCode::SEM001_ASSERT_FAILED,                Severity::Error,   "SEM001", "Assertion failed at runtime"                     },
    { ErrorCode::SEM002_ISOLATED_EXPRESSION,          Severity::Error,   "SEM002", "Isolated Expression"                             },

    // RUN
    { ErrorCode::RUN001_DIVISION_BY_ZERO,             Severity::Error,   "RUN001", "Division by zero at runtime"                     },
    { ErrorCode::RUN002_FILTER_ALL_FALSE,             Severity::Error,   "RUN002", "KEEP IF mask is all-false; data frame emptied"   },
    { ErrorCode::RUN003_DROP_ALL_TRUE,                Severity::Error,   "RUN003", "DROP IF mask is all-true; data frame emptied"    },
    { ErrorCode::RUN004_IMPLICIT_CAST_FAILURE,        Severity::Error,   "RUN004", "Implicit cast failed for one or more elements"   },

    // Warnings
    { ErrorCode::W_SEM001_REMOVE_ALL_COLUMNS,         Severity::Warning, "W-SEM001","REMOVE will drop all columns from data frame"  },
    { ErrorCode::W_TYP001_IMPLICIT_CAST,              Severity::Warning, "W-TYP001","Implicit type cast will be applied"            },
    { ErrorCode::W_SEM002_CREATE_SCALAR_BROADCAST,    Severity::Warning, "W-SEM002","Scalar expression will be broadcast to vector" },
    { ErrorCode::W_SEM003_SET_SCALAR_BROADCAST,       Severity::Warning, "W-SEM003","Scalar expression will be broadcast to column" },
}};
};

inline std::string_view severityLabel(const Severity s) noexcept {
    switch (s) {
        case Severity::Error:   return "error";
        case Severity::Warning: return "warning";
    }
    return "unknown";
}

} // namespace fluxpp