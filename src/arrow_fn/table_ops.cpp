#include "table_ops.hpp"
#include <arrow/compute/api.h>

arrow::Result<std::shared_ptr<arrow::Table>> afn::DropNullsOn(const std::string &on_field,
    const std::shared_ptr<arrow::Table> &table) {

    const auto schema = table->schema();
    const auto field = schema->GetFieldIndex(on_field);
    if (field == -1) {
        return arrow::Result<std::shared_ptr<arrow::Table>>(nullptr);
    }

    const std::vector<arrow::Datum> eq_args = { table->column(field), arrow::Datum(std::make_shared<arrow::NullScalar>())};
    ARROW_ASSIGN_OR_RAISE(const auto is_empty_res, arrow::compute::CallFunction("equal", eq_args));

    arrow::compute::FilterOptions filter_options;
    filter_options.null_selection_behavior = arrow::compute::FilterOptions::DROP;
    ARROW_ASSIGN_OR_RAISE(const auto result, arrow::compute::Filter(table, is_empty_res));
    const auto mtb = result.table();
    if (mtb == nullptr) {
        return arrow::Result<std::shared_ptr<arrow::Table>>(nullptr);
    }
    return mtb;
}

arrow::Result<std::shared_ptr<arrow::Table>> afn::DropAllNulls(const std::shared_ptr<arrow::Table> &table) {

    arrow::Datum mask = arrow::Datum(true);

    for (int i = 0; i < table->num_columns(); i++) {
        const auto column = table->column(i);
        const auto type = column->type()->id();
        ARROW_ASSIGN_OR_RAISE(const auto is_valid, arrow::compute::IsValid(column));
        switch (type) {
            case arrow::Type::BOOL:
            case arrow::Type::STRING:
            case arrow::Type::TIMESTAMP:
            case arrow::Type::INT64: {
                ARROW_ASSIGN_OR_RAISE(mask, arrow::compute::KleeneAnd(mask, is_valid));
                break;
            }
            case arrow::Type::DOUBLE: {
                ARROW_ASSIGN_OR_RAISE(const auto is_fin, arrow::compute::CallFunction("is_finite", { column }));
                ARROW_ASSIGN_OR_RAISE(const auto combined, arrow::compute::And(is_valid, is_fin));
                ARROW_ASSIGN_OR_RAISE(mask, arrow::compute::KleeneAnd(mask, combined));
                break;
            }
            case arrow::Type::MAX_ID:
            default:
                break;
        }
    }

    ARROW_ASSIGN_OR_RAISE(const auto result, arrow::compute::Filter(table, mask));
    const auto mtb = result.table();
    if (mtb == nullptr) {
        return arrow::Result<std::shared_ptr<arrow::Table>>(nullptr);
    }
    return mtb;
}
