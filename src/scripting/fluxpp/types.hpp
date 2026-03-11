#pragma once

#include <cstdint>

namespace scripting::fluxpp {
    enum class Type {
        TNULL = -1,
        TREAL = 0,
        TBOOL = 1,
        TTIMESTAMP = 2,
        TSTRING = 3,
    };

    inline bool is_type_compat(const Type lhs, const Type rhs) {
        if (lhs == rhs) return true;
        if (lhs == Type::TNULL || rhs == Type::TNULL) return true;
        else return false;
    }

    inline std::string to_string(const Type type) {
        switch (type) {
            case Type::TNULL:
                return "NULL";
            case Type::TREAL:
                return "REAL";
            case Type::TBOOL:
                return "BOOL";
            case Type::TTIMESTAMP:
                return "TIMESTAMP";
            case Type::TSTRING:
                return "STRING";
        }
    }
};
