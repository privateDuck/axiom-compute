#pragma once

#include <arrow/api.h>
namespace afn {

    arrow::Result<std::shared_ptr<arrow::Table>> DropDuplicates(const std::shared_ptr<arrow::Table>& table, int64_t& out_num_rows);
    arrow::Result<std::shared_ptr<arrow::Table>> DropAllNullColumns(const std::shared_ptr<arrow::Table>& table, std::vector<std::string>& out_dropped_columns);
    arrow::Result<std::shared_ptr<arrow::Table>> DropZeroVarianceColumns(const std::shared_ptr<arrow::Table>& table, std::vector<std::string>& out_dropped_columns);
    arrow::Result<std::shared_ptr<arrow::Table>> DropLowVarianceStringColumns(const std::shared_ptr<arrow::Table>& table, std::vector<std::string>& out_dropped_columns);

    arrow::Result<std::shared_ptr<arrow::Table>> DropNullsOn(const std::string& on_field, const std::shared_ptr<arrow::Table>& table);
    arrow::Result<std::shared_ptr<arrow::Table>> DropAllNulls(const std::shared_ptr<arrow::Table>& table);

}