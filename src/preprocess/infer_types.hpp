#pragma once

#include <array>
#include <types.hpp>
#include <utility>
#include <vector>

namespace preprocess {

    struct InferParseResult {
        Type type;
        float success_rate;
        bool full_match;
    };

    struct alignas(8) TypeInfo {
        float confidence = 0.0f;
        Type type {TSTRING};
        uint8_t _pad_[3]{};

        TypeInfo(const float conf, const Type type) : confidence(conf), type(type) {}
    };

    struct alignas(16) ColumnTypeInference {
        std::vector<TypeInfo> types;
        std::string any_error;
        Type original;

        explicit ColumnTypeInference(std::string  error) : any_error(std::move(error)), original(TSTRING) {}

        explicit ColumnTypeInference(const Type original, const Type type, const float confidence) : original(original) {
            types.emplace_back(confidence, type);
        }

        void AddAlternative(const Type type, const float confidence) {
            types.emplace_back(confidence, type);
        }
    };

    using Confidences = std::array<InferParseResult, 5>;

}
