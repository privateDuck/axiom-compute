#pragma once

#include <arrow/api.h>
#include "source_validation.hpp"
#include "infer_types.hpp"

namespace preprocess {

    struct PreprocessorContext {
        std::shared_ptr<arrow::Table> table;
        int32_t step;
    };

    PreprocessorContext* make_preprocessor_context();
    afn::RowWiseStringDF validate_source(SourceType source, const std::string& args);
    afn::RowWiseStringDF import_and_infer_types(PreprocessorContext* ctx, SourceType source, const std::string& import_args);
    afn::RowWiseStringDF type_cast_and_null_check(PreprocessorContext* ctx, const std::string& type_infer_map);
    afn::RowWiseStringDF drop_nulls_and_save(PreprocessorContext* ctx, const std::string& drop_rules, const std::string& save_location);
    void destroy_preprocessor_context(PreprocessorContext* ctx);
}
