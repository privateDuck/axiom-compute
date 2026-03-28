#include "infer_types.hpp"

#include <arrow/api.h>
#include <arrow/compute/api.h>

float try_parse_real(const std::shared_ptr<arrow::Array>& array) {
    // Steps
    // Remove all non numeric (except e,E,.,-) characters
    const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
    auto null_count_prior = arrow::compute::CallFunction("count", {array}, &null_opts);

    arrow::compute::ReplaceSubstringOptions options {
        R"([^0-9+\-.eE])",""
    };
    const auto cleaned = arrow::compute::CallFunction("replace_substring_regex", { array }, &options);

    const std::string strict_num_pattern = R"(^[+-]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][+-]?[0-9]+)?$)";
    const arrow::compute::MatchSubstringOptions match_opts(strict_num_pattern);
    auto validation_result = arrow::compute::CallFunction("match_substring_regex", {cleaned.ValueOrDie()}, &match_opts);
    const auto sum_result = arrow::compute::CallFunction("sum", {validation_result.ValueOrDie()});

    const auto total_valid_floats = sum_result.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
    const auto total_rows = array->length();
    const auto valid_float_rate = static_cast<float>(total_valid_floats) / static_cast<float>(total_rows);

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

    return valid_float_rate;
}

float try_parse_int(const std::shared_ptr<arrow::Array>& array) {
    const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
    auto null_count_prior = arrow::compute::CallFunction("count", {array}, &null_opts);

    arrow::compute::ReplaceSubstringOptions options {
        R"([^0-9+\-])",""
    };
    const auto cleaned = arrow::compute::CallFunction("replace_substring_regex", { array }, &options);

    const std::string strict_num_pattern = R"(^[+-]?[0-9]+$)";
    const arrow::compute::MatchSubstringOptions match_opts(strict_num_pattern);
    auto validation_result = arrow::compute::CallFunction("match_substring_regex", {cleaned.ValueOrDie()}, &match_opts);
    const auto sum_result = arrow::compute::CallFunction("sum", {validation_result.ValueOrDie()});

    const auto total_valid_floats = sum_result.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
    const auto total_rows = array->length();
    const auto valid_int_rate = static_cast<float>(total_valid_floats) / static_cast<float>(total_rows);
    return valid_int_rate;
}

float try_parse_bool(const std::shared_ptr<arrow::Array>& array) {
    const arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
    const auto null_count_prior = arrow::compute::CallFunction("count", {array}, &null_opts);

    arrow::compute::MatchSubstringOptions opt;
    opt.pattern = R"(^\s*(true|false|t|f|yes|no|y|n|on|off|0|1|-1)\s*$)";
    opt.ignore_case = true;
    const auto count_matches = arrow::compute::CallFunction("count_substring_regex", { array }, &opt);

    const auto count_opt = arrow::compute::CountOptions{arrow::compute::CountOptions::ALL};
    const auto count = arrow::compute::Count(array, count_opt).ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
    const auto proper_counts_matches = count_matches.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
    const auto proper_null_counts = null_count_prior.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;
    const auto fails = count - proper_counts_matches;

    const auto success_rate = static_cast<float>(proper_counts_matches) / static_cast<float>(count);
    return success_rate;
}

float try_parse_timestamp(const std::shared_ptr<arrow::Array>& array) {

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
    const auto count_opt = arrow::compute::CountOptions{arrow::compute::CountOptions::ALL};
    const auto count = arrow::compute::Count(array, count_opt).ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

    const auto null_count_after = nulls_after.ValueOrDie().scalar_as<arrow::UInt64Scalar>().value;

    const auto success_rate = static_cast<float>(null_count_after - null_count_prior) / static_cast<float>(count);
    return success_rate;
}