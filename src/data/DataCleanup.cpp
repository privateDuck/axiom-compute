#include "DataCleanup.hpp"
#include <arrow/compute/api.h>

bool CheckTypeMatch(std::shared_ptr<arrow::Array> string_col, std::string regex_pattern, double threshold)
{

    arrow::compute::ExecContext context;
    arrow::compute::MatchSubstringOptions options(regex_pattern);

    // "match_substring_regex" returns a BooleanArray (true if matches, false if not)
    auto match_result = arrow::compute::CallFunction("match_substring_regex", { string_col }, &options, &context);

    if (!match_result.ok()) {
        std::cerr << "Regex failed: " << match_result.status().ToString() << std::endl;
        return false;
    }

    std::shared_ptr<arrow::Array> match_bools = match_result->make_array();

    auto sum_result = arrow::compute::CallFunction("sum", { match_bools }, &context);

    if (!sum_result.ok()) {
        return false;
    }

    uint64_t match_count = std::static_pointer_cast<arrow::UInt64Scalar>(sum_result->scalar())->value;
    int64_t total_rows = string_col->length();

    double match_percentage = (double)match_count / total_rows;

    return match_percentage >= threshold;
}

std::shared_ptr<arrow::DoubleArray> CleanAndCastToDouble(std::shared_ptr<arrow::StringArray> raw_string_array)
{
    arrow::compute::ExecContext context;
    
    arrow::compute::ReplaceSubstringOptions replace_opts(
        "[^0-9\\-eE.]", // Match anything that is NOT a number char
        ""              
    );

    auto clean_res = arrow::compute::CallFunction("replace_substring_regex", { raw_string_array }, &replace_opts, &context);
    if (!clean_res.ok()) {
		return nullptr;
    }
    auto current_array = clean_res->make_array();


    std::vector<arrow::Datum> args = { current_array, arrow::Datum("")};
    auto is_empty_res = arrow::compute::CallFunction("equal", args, &context);
    if (!is_empty_res.ok()) {
		return nullptr;
    }
    auto is_empty_mask = is_empty_res->make_array();

    auto nullified_res = arrow::compute::CallFunction("if_else", {
        is_empty_mask,
        arrow::Datum(std::make_shared<arrow::NullScalar>()),
        current_array                                        
    }, &context);

	if (!nullified_res.ok()) {
		return nullptr;
    }
	current_array = nullified_res->make_array();

    arrow::compute::CastOptions cast_opts;
    cast_opts.to_type = arrow::float64();

    auto cast_res = arrow::compute::Cast(current_array, cast_opts);

    if (!cast_res.ok()) {
        std::cerr << "Cast failed for some rows: " << cast_res.status().ToString() << '\n';
        return nullptr;
    }

    return std::static_pointer_cast<arrow::DoubleArray>(cast_res->make_array());
}

void CleanUpStringArray(std::shared_ptr<arrow::StringArray> array)
{

}
