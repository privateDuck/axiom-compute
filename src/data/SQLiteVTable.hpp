#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct MatrixColData {
	std::string column_name;

};

struct MatrixData {
	float* data_ptr;
	int32_t rows;
	int32_t cols;
	std::vector<std::string> column_names;
	std::string table_name;
};

// SQLite Virtual Table around a pointer to a contiguous block of data
class SQLiteVTable {
};