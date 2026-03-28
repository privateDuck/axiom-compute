#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <cassert>

namespace exec::expr {

    enum class ErrorCode : uint32_t {
        E001_SYNTAX_ERROR               = 001,
        E002_PARSING_ERROR              = 002,
        E101_UNKNOWN_REFERENCE          = 101,
        E201_TYPE_MISMATCH              = 201,
        E202_NON_BOOLEAN_CONDITION      = 202,
        E203_TERNARY_BRANCH_MISMATCH    = 203,
        E204_BINARY_OPERAND_MISMATCH    = 204,
        E205_UNARY_OPERAND_MISMATCH     = 205,
        E206_IMPLICIT_CAST_FAILURE      = 206,
        E301_UNSUPPORTED_OPERATION      = 301,
        E302_UNSUPPORTED_ARGUMENT_TYPE  = 302,
        E303_NON_VECTOR_AGGREGATE       = 303,
        E401_DIVIDE_BY_ZERO             = 401,
        E901_IMPCAST_PREC_LOSS_WARNING  = 901,
        E902_IMPCAST_WIDENING_WARNING   = 902,
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
    { ErrorCode::E001_SYNTAX_ERROR,                   Severity::Error,   "E001", "Syntax error encountered. Unexpected token or malformed expression"},
    { ErrorCode::E002_PARSING_ERROR,                  Severity::Error,   "E002", "Parsing failed. The expression structure could not be resolved"},
    { ErrorCode::E101_UNKNOWN_REFERENCE,              Severity::Error,   "E101", "Unresolved reference. The specified identifier is not defined in the data frame"},
    { ErrorCode::E201_TYPE_MISMATCH,                  Severity::Error,   "E201", "Type mismatch. The provided data type is incompatible with the expected type for this context"},
    { ErrorCode::E202_NON_BOOLEAN_CONDITION,          Severity::Error,   "E202", "Invalid condition. The control expression must evaluate to a boolean"},
    { ErrorCode::E203_TERNARY_BRANCH_MISMATCH,        Severity::Error,   "E203", "Ternary branch type mismatch. Both branches of the conditional expression must evaluate to the same data type"},
    { ErrorCode::E204_BINARY_OPERAND_MISMATCH,        Severity::Error,   "E204", "Binary operand type mismatch. The left and right operands must evaluate to the same data type"},
    { ErrorCode::E205_UNARY_OPERAND_MISMATCH,         Severity::Error,   "E001", ""  },
    { ErrorCode::E206_IMPLICIT_CAST_FAILURE,          Severity::Error,   "E002", "CREATE identifier already exists as column"      },
    { ErrorCode::E301_UNSUPPORTED_OPERATION,          Severity::Error,   "E301", "Operator not defined for the type"               },
    { ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE,      Severity::Error,   "E302", "Function does not support the type"              },
    { ErrorCode::E303_NON_VECTOR_AGGREGATE,           Severity::Error,   "E303", "Aggregate functions requires a vector argument"  },
    { ErrorCode::E401_DIVIDE_BY_ZERO,                 Severity::Error,   "E401", "Attempt to division by zero in expression"       },
    { ErrorCode::E901_IMPCAST_PREC_LOSS_WARNING,      Severity::Error,   "E007", "Implicit cast applied. Precision may be lost"    },
    { ErrorCode::E902_IMPCAST_WIDENING_WARNING,       Severity::Error,   "E008", "Implicit cast applied. Integer to Real"          },
}};
};

inline std::string_view severityLabel(const Severity s) noexcept {
    switch (s) {
        case Severity::Error:   return "error";
        case Severity::Warning: return "warning";
    }
    return "unknown";
}

}
