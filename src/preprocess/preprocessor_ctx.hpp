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

    // Validates the input
    SourceValidationResult validate_source(SourceType source, const std::string& args);

    // Import the file using the given import arguments, load the data frame into, infer types, return the type inference result
    TypeInferenceResult import_and_infer_types(PreprocessorContext* ctx, SourceType source, const std::string& import_args);

    // convert/coerce each column into the specified type
    // if coercion failed, set the value to null
    // count the nulls
    // perform data quality conforms: deduplication (row wise), zero variance (any-t) column, all null (any-t), var factor <= 10 (string-t)
    void type_cast_and_null_check(PreprocessorContext* ctx, const std::string& type_infer_map);

    // perform specified null removal operations (all, column based), returns the number of rows affected/removed.
    uint64_t drop_nulls_and_save(PreprocessorContext* ctx, const std::string& drop_rules, const std::string& save_location);

    // perform any specified transforms. manual cell edits, column rearrangement, column re-namings, column drops.
    // Then immediately saves the dataframe to the disk at the given path.
    void manual_ops_save(PreprocessorContext* ctx, const std::string& manual_ops, const std::string& save_location);

    void destroy_preprocessor_context(PreprocessorContext* ctx);
}
