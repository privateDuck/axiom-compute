#include "infer_types.hpp"

#include <arrow/api.h>
#include <arrow/compute/api.h>
#include "../context/GlobalContextHandle.hpp"

namespace preprocess {
    InferParseResult try_parse_real(const std::shared_ptr<arrow::Array>& array) {
        // Steps
        // Remove all non-numeric leading and trailing characters
        // Validate the structure of the remaining string to ensure it matches a valid float pattern
        const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
        auto null_count_res = arrow::compute::CallFunction("count", {array}, &null_opts);
        auto null_count_prior = null_count_res.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

        const arrow::compute::ReplaceSubstringOptions options {
            R"(^[^0-9+\-]+|[^0-9]+$)",""
        };
        const auto cleaned = arrow::compute::CallFunction("replace_substring_regex", { array }, &options);

        const std::string strict_num_pattern = R"(^[+-]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][+-]?[0-9]+)?$)";
        const arrow::compute::MatchSubstringOptions match_opts(strict_num_pattern);
        auto validation_result = arrow::compute::CallFunction("match_substring_regex", {cleaned.ValueOrDie()}, &match_opts);
        const auto sum_result = arrow::compute::CallFunction("sum", {validation_result.ValueOrDie()});

        const auto total_valid_floats = sum_result.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
        const auto total_valid_rows = array->length() - null_count_prior;
        const auto valid_float_rate = static_cast<float>(total_valid_floats) / static_cast<float>(total_valid_rows);

        return {TREAL, valid_float_rate, total_valid_floats == total_valid_rows};

        /*
        const std::vector eq_args = { cleaned.ValueOrDie(), arrow::Datum("")};
        const auto is_empty_res = arrow::compute::CallFunction("equal", eq_args);

        const auto nullified = arrow::compute::CallFunction("if_else", {
            is_empty_res.ValueOrDie(),
            arrow::Datum(std::make_shared<arrow::NullScalar>()),
            cleaned.ValueOrDie()
        });

        auto cast_options = arrow::compute::CastOptions::Safe();
        cast_options.to_type = arrow::float64();
        auto cast_result = arrow::compute::Cast(nullified.ValueOrDie(), cast_options);
        auto null_count = arrow::compute::CallFunction("count", {cast_result.ValueOrDie()}, &null_opts);

        const auto count_opt = arrow::compute::CountOptions{arrow::compute::CountOptions::ALL};
        const auto count = arrow::compute::Count(array, count_opt).ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

        const auto proper_nullc = null_count.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
        const auto proper_prior_nullc = null_count_prior.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
        const auto fails = proper_nullc - proper_prior_nullc;

        const auto success_rate = static_cast<float>(count - fails) / static_cast<float>(count);
        // const auto fail_rate = 1.0 - success_rate;
        */
    }

    InferParseResult try_parse_int(const std::shared_ptr<arrow::Array>& array) {
        // Steps
        // Remove all non-numeric leading and trailing characters
        // Validate the structure of the remaining string to ensure it matches a valid integer pattern
        const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
        auto null_count_res = arrow::compute::CallFunction("count", {array}, &null_opts);
        auto null_count_prior = null_count_res.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

        const arrow::compute::ReplaceSubstringOptions options {
            R"(^[^0-9+\-]+|[^0-9]+$)",""
        };
        const auto cleaned = arrow::compute::CallFunction("replace_substring_regex", { array }, &options);

        const std::string strict_num_pattern = R"(^[+-]?[0-9]+$)";
        const arrow::compute::MatchSubstringOptions match_opts(strict_num_pattern);
        auto validation_result = arrow::compute::CallFunction("match_substring_regex", {cleaned.ValueOrDie()}, &match_opts);
        const auto sum_result = arrow::compute::CallFunction("sum", {validation_result.ValueOrDie()});

        const auto total_valid_ints = sum_result.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
        const auto total_valid_rows = array->length() - null_count_prior;
        const auto valid_float_rate = static_cast<float>(total_valid_ints) / static_cast<float>(total_valid_rows);

        return {TINT, valid_float_rate, total_valid_ints == total_valid_rows};
    }

    InferParseResult try_parse_bool(const std::shared_ptr<arrow::Array>& array) {
        const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_VALID};
        const auto valid_rows_res = arrow::compute::CallFunction("count", {array}, &null_opts);
        const auto valid_rows = valid_rows_res.ValueUnsafe().scalar_as<arrow::UInt64Scalar>().value;

        arrow::compute::MatchSubstringOptions opt;
        opt.pattern = R"(^\s*(true|false|t|f|yes|no|y|n|on|off|0|1|-1)\s*$)";
        opt.ignore_case = true;
        const auto count_matches_res = arrow::compute::CallFunction("count_substring_regex", { array }, &opt);
        const auto matching_rows = count_matches_res.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;


        const auto success_rate = static_cast<float>(matching_rows) / static_cast<float>(valid_rows);
        return {TBOOL, success_rate, valid_rows == matching_rows};
    }

    InferParseResult try_parse_timestamp(const std::shared_ptr<arrow::Array>& array) {

        const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
        const auto nulls_prior = arrow::compute::CallFunction("count", {array}, &null_opts);
        const auto null_count_prior = nulls_prior.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

        arrow::compute::StrptimeOptions opt;
        opt.error_is_null = true;
        opt.unit = arrow::TimeUnit::SECOND;

        opt.format = "%Y-%m-%dT%H:%M:%S";
        const auto fmt_datetime = arrow::compute::CallFunction("strptime", { array }, &opt);
        opt.format = "%H:%M:%S";
        const auto fmt_time = arrow::compute::CallFunction("strptime", { array }, &opt);
        opt.format = "%Y-%m-%d";
        const auto fmt_date = arrow::compute::CallFunction("strptime", { array }, &opt);

        const auto fmt_set = arrow::compute::CallFunction("coalesce", { fmt_datetime.ValueOrDie(), fmt_time.ValueOrDie(), fmt_date.ValueOrDie() });

        const auto nulls_after = arrow::compute::CallFunction("count", {fmt_set.ValueOrDie()}, &null_opts);
        const auto count = array->length();

        const auto null_count_after = nulls_after.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

        const auto success_rate = static_cast<float>(null_count_after - null_count_prior) / static_cast<float>(count);
        return {TTIMESTAMP, success_rate, null_count_after == null_count_prior};
    }


    ColumnTypeInference infer_type_of_array(const std::shared_ptr<arrow::Array>& array, const std::string& name) {
        Confidences confidences;
        confidences[TREAL] = {TREAL, 0.0f, false};
        confidences[TINT] = {TINT, 0.0f, false};
        confidences[TBOOL] = {TBOOL, 0.0f, false};
        confidences[TSTRING] = {TSTRING, 0.0f, true};
        confidences[TTIMESTAMP] = {TTIMESTAMP, 0.0f, false};

        const arrow::compute::CountOptions opt = arrow::compute::CountOptions(arrow::compute::CountOptions::ONLY_VALID);
        const auto dist_result = arrow::compute::CallFunction("count_distinct", { array }, &opt);
        const auto valid_result = arrow::compute::CallFunction("count", { array }, &opt);

        if (!dist_result.ok() || !valid_result.ok()) {
            return ColumnTypeInference("Invalid Data");
        }

        const auto count_distinct = dist_result->scalar_as<arrow::UInt64Scalar>().value;
        const auto count_valid = valid_result->scalar_as<arrow::UInt64Scalar>().value;
        const auto distinct_percent = static_cast<float>(count_distinct) / static_cast<float>(count_valid);
        const auto count_null = array->length() - count_valid;

        auto add_categorical_conf = [count_distinct, distinct_percent](ColumnTypeInference& res) {
            if (count_distinct <= 5) {
                res.AddAlternative(TSTRING, 1.0f);
            }
            else if (count_distinct <= 10) {
                res.AddAlternative(TSTRING, 0.9f);
            }
            else if (distinct_percent < 0.5f){
                res.AddAlternative(TSTRING, 0.9f * std::exp(-0.03f * static_cast<float>(count_distinct - 10)));
            }
        };

        if (count_distinct <= 1) {
            // Column contains a singular value. Will be automatically removed in the next step
            return ColumnTypeInference("Singular Column");
        }

        switch (array->type_id()) {
            case arrow::Type::NA:
                break;
            case arrow::Type::BOOL: {
                auto res = ColumnTypeInference(array, name, TBOOL, TBOOL, 1.0f, count_distinct, count_null);
                res.AddAlternative(TINT, 1.0f);
                res.AddAlternative(TREAL, 1.0f);
                return res;
            }
            case arrow::Type::UINT8:
            case arrow::Type::INT8:
            case arrow::Type::UINT16:
            case arrow::Type::INT16:
            case arrow::Type::UINT32:
            case arrow::Type::INT32:
            case arrow::Type::UINT64:
            case arrow::Type::INT64: {
                auto res = ColumnTypeInference(array, name, TINT, TINT, 1.0f, count_distinct, count_null);
                res.AddAlternative(TREAL, 1.0f);
                add_categorical_conf(res);
                return res;
            }
            case arrow::Type::HALF_FLOAT:
            case arrow::Type::FLOAT:
            case arrow::Type::DECIMAL:
            case arrow::Type::DECIMAL256:
            case arrow::Type::DECIMAL32:
            case arrow::Type::DECIMAL64:
            case arrow::Type::DOUBLE:{
                auto res = ColumnTypeInference(array, name, TREAL, TREAL, 1.0f, count_distinct, count_null);
                add_categorical_conf(res);
                return res;
            }
            case arrow::Type::STRING:
            case arrow::Type::BINARY:
            case arrow::Type::FIXED_SIZE_BINARY:
            case arrow::Type::STRING_VIEW:
            case arrow::Type::BINARY_VIEW: {
                // Custom inferencing
                break;
            }
            case arrow::Type::DATE32:
            case arrow::Type::DATE64:
            case arrow::Type::TIMESTAMP:
            case arrow::Type::TIME32:
            case arrow::Type::TIME64: {
                auto res = ColumnTypeInference(array, name, TTIMESTAMP, TTIMESTAMP, 1.0f, count_distinct, count_null);
                add_categorical_conf(res);
                return res;
            }
            case arrow::Type::INTERVAL_MONTHS:
            case arrow::Type::INTERVAL_DAY_TIME:
            case arrow::Type::DURATION:
            case arrow::Type::INTERVAL_MONTH_DAY_NANO: {
                auto res = ColumnTypeInference(array, name, TREAL, TREAL, 1.0f, count_distinct, count_null);
                add_categorical_conf(res);
                return res;
            }
            case arrow::Type::LIST:
            case arrow::Type::STRUCT:
            case arrow::Type::SPARSE_UNION:
            case arrow::Type::DENSE_UNION:
            case arrow::Type::DICTIONARY:
            case arrow::Type::MAP:
            case arrow::Type::EXTENSION:
            case arrow::Type::FIXED_SIZE_LIST:
            case arrow::Type::LARGE_LIST:
            case arrow::Type::RUN_END_ENCODED:
            case arrow::Type::LIST_VIEW:
            case arrow::Type::LARGE_LIST_VIEW:
            case arrow::Type::LARGE_BINARY:
            case arrow::Type::LARGE_STRING: {
                // Not supported
                return ColumnTypeInference("Unsupported Data Types");
            }
            case arrow::Type::MAX_ID:
            default: {
                // Error
                return ColumnTypeInference("Unknown Data Type");
            }
        }

        confidences[TBOOL] = try_parse_bool(array);
        if (confidences[TBOOL].full_match) {
            auto res = ColumnTypeInference(array, name, TSTRING, TBOOL, 1.0f, count_distinct, count_null);
            add_categorical_conf(res);
            return res;
        }
        confidences[TTIMESTAMP] = try_parse_timestamp(array);
        if (confidences[TTIMESTAMP].full_match) {
            auto res = ColumnTypeInference(array, name, TSTRING, TTIMESTAMP, 1.0f, count_distinct, count_null);
            add_categorical_conf(res);
            return res;
        }
        confidences[TINT] = try_parse_int(array);
        if (confidences[TINT].full_match) {
            auto res = ColumnTypeInference(array, name, TSTRING, TINT, 1.0f, count_distinct, count_null);
            res.AddAlternative(TREAL, 1.0f);
            add_categorical_conf(res);
            return res; // This can also be parsed as float. But we're giving the user the choice
        }
        confidences[TREAL] = try_parse_real(array);
        if (confidences[TREAL].success_rate >= confidences[TINT].success_rate || confidences[TREAL].full_match) {
            auto res = ColumnTypeInference(array, name, TSTRING, TREAL, 1.0f, count_distinct, count_null);
            add_categorical_conf(res);
            return res;
        }

        std::ranges::sort(confidences, [](const InferParseResult& a, const InferParseResult& b) {
            return a.success_rate > b.success_rate;
        });

        float conf_success;
        Type conf_type;
        if (confidences[0].success_rate <= 0.5) {
            // If no type gets a majority of success rate, In this case String type will dominate
            if (count_distinct <= 5) {
                conf_success = 1.0f;
            }
            else if (count_distinct <= 10) {
                conf_success = 0.9f;
            }
            else if (distinct_percent < 0.5f){
                conf_success = 0.9f * std::exp(-0.03f * static_cast<float>(count_distinct - 10));
            }
            else {
                return ColumnTypeInference("Low Variance");
            }
            conf_type = TSTRING;
        }
        else {
            conf_type = confidences[0].type;
            conf_success = confidences[0].success_rate;
        }
        auto res = ColumnTypeInference(array, name, TSTRING, conf_type, conf_success, count_distinct, count_null);

        for (int i = 1; i < confidences.size() - 1; i++) {
            if (confidences[i].success_rate > 0.1f) {
                res.AddAlternative(confidences[i].type, confidences[i].success_rate);
            }
        }

        if (confidences[0].success_rate > 0.5)
            add_categorical_conf(res);

        return res;
    }

    TypeInferenceResult infer_types_of_table(const std::shared_ptr<arrow::Table>& table) {
        std::vector<ColumnTypeInference> results;
        std::string result_error;
        const auto fields = table->fields();
        for (int i = 0; i < table->num_columns(); i++) {
            const auto res = infer_type_of_array(table->column(i)->chunk(0), fields[i]->name());
            if (!res.any_error.empty() && result_error.empty()) {
                result_error = res.any_error;
            }
            results.emplace_back(res);
        }
        return {results, result_error};
    }
};