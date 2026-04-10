#pragma once

#include <arrow/api.h>
namespace afn {

    arrow::Result<std::shared_ptr<arrow::Table>> DropNullsOn(const std::string& on_field, const std::shared_ptr<arrow::Table>& table);
    arrow::Result<std::shared_ptr<arrow::Table>> DropAllNulls(const std::shared_ptr<arrow::Table>& table);
    arrow::Result<std::shared_ptr<arrow::Table>> DropDuplicates(const std::shared_ptr<arrow::Table>& table);

}