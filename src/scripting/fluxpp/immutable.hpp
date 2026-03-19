
#pragma once

#include <string>
#include "types.hpp"

namespace scripting::fluxpp {
    struct Immutable {
        std::string id;
        Type type;
        bool isVector = false;
        uint32_t line = 0;
        bool is_used  = false;
        uint16_t loc = 0;

        Immutable(std::string id, const Type type, const bool isVec, const uint64_t line)
            : id(std::move(id)), type(type), isVector(isVec), line(line) {}

        bool operator==(const Immutable& other) const {
            return id == other.id && type == other.type && isVector == other.isVector;
        }
    };


    struct ImmutableHasher {
        size_t operator()(const Immutable& p) const noexcept {
            size_t h1 = std::hash<std::string>{}(p.id);
            h1 ^= (std::hash<fluxpp::Type>{}(p.type) << 1);
            h1 ^= (std::hash<bool>{}(p.isVector) << 1);
            return h1;
        }
    };

}