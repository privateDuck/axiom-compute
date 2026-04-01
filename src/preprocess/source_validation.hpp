#pragma once

#include <arrow/api.h>
#include "types.hpp"

namespace preprocess {

    struct ValidationResult {
        char* source_head;
        int32_t source_head_char_length;
        int32_t cols;
        int32_t rows;
        bool valid_source;

        ValidationResult(const bool source_state) : source_head(nullptr), source_head_char_length(0), cols(0), rows(0), valid_source(source_state) {
        }
    };

    bool Validate(SourceType src, const std::vector<std::string>& args);

}
