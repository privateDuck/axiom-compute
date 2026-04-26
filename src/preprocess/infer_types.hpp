#pragma once

#include <array>
#include <types.hpp>
#include <utility>
#include <vector>
#include <arrow/api.h>

#include "../arrow_fn/string_df.hpp"

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

    struct ColumnTypeInference {
        afn::RowWiseStringDF sample;
        std::string name;
        std::vector<TypeInfo> types;
        std::string any_error;
        uint64_t unique_values;
        uint64_t null_count;
        Type original;

        explicit ColumnTypeInference(std::string  error) : any_error(std::move(error)), unique_values(0), null_count(0), original(TSTRING) {}

        explicit ColumnTypeInference(const std::shared_ptr<arrow::Array>& array, std::string name, const Type original, const Type type, const float confidence, const uint64_t uniqueC, const uint64_t nullC)
        : name(std::move(name)), unique_values(uniqueC), null_count(nullC), original(original) {
            sample.Initialize(array, name, 100);
            types.emplace_back(confidence, type);
        }

        void AddAlternative(const Type type, const float confidence) {
            types.emplace_back(confidence, type);
        }
    };

    struct TypeInferenceResult {
        std::vector<ColumnTypeInference> column_inferences;
        std::string any_errors;
    };

    TypeInferenceResult infer_types_of_table(const std::shared_ptr<arrow::Table>& table);

    using Confidences = std::array<InferParseResult, 5>;

}
