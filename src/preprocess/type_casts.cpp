#include "type_casts.hpp"

#include <arrow/compute/api.h>


namespace preprocess {
    arrow::Status CastOrCoerceTable(std::shared_ptr<arrow::Table> &table,
        const std::unordered_map<std::string, arrow::Type::type> &types, const std::string& additional) {
        size_t index = 0;
        for (const auto& [name, type] : types) {
            const auto col = table->column(index);
            switch (type) {
                case arrow::Type::BOOL: {
                    arrow::compute::MatchSubstringOptions opt;
                    opt.ignore_case = true;
                    opt.pattern = R"(^\s*(true|t|yes|y|on|1|-1)\s*$)";
                    ARROW_ASSIGN_OR_RAISE(const auto pos, arrow::compute::CallFunction("match_substring_regex", {col}, &opt));
                    const auto new_field = arrow::field(name, pos.type());
                    ARROW_ASSIGN_OR_RAISE(table, table->SetColumn(index, new_field, pos.chunked_array()));
                    break;
                }
                case arrow::Type::STRING: {
                    arrow::compute::CastOptions opt = arrow::compute::CastOptions::Unsafe();
                    opt.to_type = arrow::utf8();
                    ARROW_ASSIGN_OR_RAISE(const auto out, arrow::compute::Cast(col, opt));
                    const auto new_field = arrow::field(name, out.type());
                    ARROW_ASSIGN_OR_RAISE(table, table->SetColumn(index, new_field, out.chunked_array()));
                    break;
                }
                case arrow::Type::TIMESTAMP: {
                    arrow::compute::StrptimeOptions opt;
                    opt.unit = arrow::TimeUnit::SECOND;
                    opt.error_is_null = true;
                    opt.format = additional.empty() ? "%Y-%m-%dT%H:%M:%S" : additional;
                    ARROW_ASSIGN_OR_RAISE(const auto out, arrow::compute::CallFunction("strptime", {col}, &opt));
                    const auto new_field = arrow::field(name, out.type());
                    ARROW_ASSIGN_OR_RAISE(table, table->SetColumn(index, new_field, out.chunked_array()));
                    break;
                }
                case arrow::Type::INT64: {
                    const arrow::compute::ReplaceSubstringOptions options {
                        R"(^[^0-9+\-]+|[^0-9]+$)",""
                    };
                    ARROW_ASSIGN_OR_RAISE(const auto cleaned, arrow::compute::CallFunction("replace_substring_regex", { col }, &options));

                    const std::vector eq_args = { cleaned, arrow::Datum("")};
                    ARROW_ASSIGN_OR_RAISE(const auto is_empty_res, arrow::compute::CallFunction("equal", eq_args));

                    ARROW_ASSIGN_OR_RAISE(const auto nullified, arrow::compute::CallFunction("if_else", {
                        is_empty_res,
                        arrow::Datum(std::make_shared<arrow::NullScalar>()),
                        cleaned
                    }));

                    arrow::compute::CastOptions opt = arrow::compute::CastOptions::Safe();
                    opt.to_type = arrow::int64();
                    ARROW_ASSIGN_OR_RAISE(const auto out, arrow::compute::Cast(nullified, opt));
                    const auto new_field = arrow::field(name, out.type());
                    ARROW_ASSIGN_OR_RAISE(table, table->SetColumn(index, new_field, out.chunked_array()));
                    break;
                }
                case arrow::Type::DOUBLE: {
                    const arrow::compute::ReplaceSubstringOptions options {
                        R"(^[^0-9+\-]+|[^0-9]+$)",""
                    };
                    ARROW_ASSIGN_OR_RAISE(const auto cleaned, arrow::compute::CallFunction("replace_substring_regex", { col }, &options));

                    const std::vector eq_args = { cleaned, arrow::Datum("")};
                    ARROW_ASSIGN_OR_RAISE(const auto is_empty_res, arrow::compute::CallFunction("equal", eq_args));

                    ARROW_ASSIGN_OR_RAISE(const auto nullified, arrow::compute::CallFunction("if_else", {
                        is_empty_res,
                        arrow::Datum(std::make_shared<arrow::NullScalar>()),
                        cleaned
                    }));

                    arrow::compute::CastOptions opt = arrow::compute::CastOptions::Safe();
                    opt.to_type = arrow::float64();
                    ARROW_ASSIGN_OR_RAISE(const auto out, arrow::compute::Cast(nullified, opt));
                    const auto new_field = arrow::field(name, out.type());
                    ARROW_ASSIGN_OR_RAISE(table, table->SetColumn(index, new_field, out.chunked_array()));
                    break;
                }
                case arrow::Type::MAX_ID:
                default:
                    break;
            }
            ++index;
        }
        return arrow::Status::OK();
    }

    arrow::Status GetNullsWRT(const std::shared_ptr<arrow::Table> &table, afn::RowWiseStringDF& df, const std::string &column, int32_t max_rows) {
        const auto col = table->GetColumnByName(column);
        ARROW_ASSIGN_OR_RAISE(const auto cont_col, arrow::Concatenate(col->chunks(), arrow::default_memory_pool()));
        arrow::compute::NullOptions nlopt;
        nlopt.nan_is_null = true;
        ARROW_ASSIGN_OR_RAISE(const auto nulls, arrow::compute::IsNull(cont_col, nlopt));
        arrow::compute::FilterOptions flopt;
        flopt.null_selection_behavior = arrow::compute::FilterOptions::NullSelectionBehavior::DROP;
        const auto filtered = arrow::compute::Filter(table, nulls, flopt);

        if (!filtered.ok()) {
            return arrow::Status::ExecutionError();
        }
        const auto filtered_table = filtered->table();
        if (filtered_table == nullptr) {
            return arrow::Status::ExecutionError();
        }
        df = afn::RowWiseStringDF(filtered_table);
        return arrow::Status::OK();
    }

    arrow::Status DropNullsWRT(std::shared_ptr<arrow::Table> &table, const std::string &column) {
        const auto col = table->GetColumnByName(column);
        ARROW_ASSIGN_OR_RAISE(const auto cont_col, arrow::Concatenate(col->chunks(), arrow::default_memory_pool()));
        ARROW_ASSIGN_OR_RAISE(const auto valids, arrow::compute::IsValid(cont_col));
        arrow::compute::FilterOptions flopt;
        flopt.null_selection_behavior = arrow::compute::FilterOptions::NullSelectionBehavior::DROP;
        const auto filtered = arrow::compute::Filter(table, valids, flopt);
        if (!filtered.ok()) {
            return arrow::Status::ExecutionError();
        }
        table = filtered.ValueOrDie().table();
        return arrow::Status::OK();
    }

    arrow::Status DropNullsWRTMany(std::shared_ptr<arrow::Table> &table, const std::vector<std::string> &columns) {
        auto mask = arrow::Datum(true);

        for (int i = 0; i < columns.size(); i++) {
            const auto column = table->GetColumnByName(columns[i]);
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
            return arrow::Status::ExecutionError();
        }
        table = mtb;
        return arrow::Status::OK();
    }
}
