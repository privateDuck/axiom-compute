#pragma once

#include <arrow/api.h>
#include <re2/re2.h>
#include <absl/container/flat_hash_map.h>

namespace data_cleanup {
	constexpr const char* url_regex = R"(https?://\S+|www\.\S+)";
	constexpr const char* email_regex = R"(\S+@\S+\.\S+)";
	constexpr const char* int_regex = "^\\s*[+-]?\\d+\\s*$";
	constexpr const char* float_regex = "^\\s*[+-]?(\\d+(\\.\\d*)?|\\.\\d+)([eE][+-]?\\d+)?\\s*$";
};


bool CheckTypeMatch(
	std::shared_ptr<arrow::Array> string_col,
	std::string regex_pattern,
	double threshold = 0.9);

std::shared_ptr<arrow::DoubleArray> CleanAndCastToDouble(std::shared_ptr<arrow::StringArray> raw_string_array);

void CleanUpStringArray(std::shared_ptr<arrow::StringArray> array);