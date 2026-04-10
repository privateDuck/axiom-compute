#pragma once
#include <cstdint>
#include <string>

enum Type : uint8_t {
    TREAL,
    TINT,
    TBOOL,
    TSTRING,
    TTIMESTAMP,
};

inline std::string_view typeName(const Type type) {
    switch (type) {
        case TREAL:
            return "REAL";
        case TINT:
            return "INT";
        case TBOOL:
            return "BOOL";
        case TSTRING:
            return "STRING";
        case TTIMESTAMP:
            return "TIMESTAMP";
    }
    return "UNKNOWN";
}

inline std::string typeNameStr(const Type type) {
    switch (type) {
        case TREAL:
            return "REAL";
        case TINT:
            return "INT";
        case TBOOL:
            return "BOOL";
        case TSTRING:
            return "STRING";
        case TTIMESTAMP:
            return "TIMESTAMP";
    }
    return "UNKNOWN";
}

inline bool canCompareType(const Type type) {
    if (type == TSTRING || type == TBOOL) return false;
    return true;
}

inline bool shouldCast(const Type lhs, const Type rhs) {
    if (lhs == TREAL || rhs == TINT) return true;
    if (lhs == TINT || rhs == TREAL) return true;
    return false;
}

inline bool isNumeric(const Type type) {
    if (type == TREAL || type == TINT) return true;
    return false;
}