#pragma once

#include <array>
#include <types.hpp>
#include <vector>

namespace preprocess {

    struct InferParseResult {
        Type type;
        float success_rate;
        bool full_match;
    };

    struct alignas(8) TypeAlternative {
        float confidence = 0.0f;
        Type type {TSTRING};
        uint8_t _pad_[3]{};
    };

    struct alignas(16) ColumnTypeInference {
        TypeAlternative alternatives[4];
        float primary_confidence;
        Type primary_type;
        uint8_t alternative_count;
        uint8_t _pad_[10];

        ColumnTypeInference() : alternatives{}, primary_confidence(0.0f), primary_type(TSTRING), alternative_count(0), _pad_{} {}

        explicit ColumnTypeInference(const Type type, const float confidence) : alternatives(), primary_type(type),
            primary_confidence(confidence), alternative_count(0), _pad_{} {
        }

        void AddAlternative(const Type type, const float confidence) {
            alternatives[alternative_count] = {confidence, type};
            ++alternative_count;
        }
    };

    struct TypeInferenceResult {
        ColumnTypeInference* inferences;
        int64_t col_count;

        explicit TypeInferenceResult(const std::vector<ColumnTypeInference>& infers) : col_count(infers.size()) {
            inferences = new ColumnTypeInference[col_count];
            for (size_t i = 0; i < infers.size(); ++i) {
                inferences[i] = infers[i];
            }
            col_count = infers.size();
        }

        ~TypeInferenceResult() {
            delete[] inferences;
        }
    };

    using Confidences = std::array<InferParseResult, 5>;

}
