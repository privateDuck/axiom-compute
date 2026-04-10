#pragma once

#include <arrow/api.h>
#include <unordered_map>
#include <string>
#include "../arrow_fn/string_df.hpp"

namespace preprocess {

    struct NullCheckResult {

    };

    arrow::Status CastOrCoerceTable(std::shared_ptr<arrow::Table> &table, const std::unordered_map<std::string, arrow::Type::type> &types, const std::string& additional);
    arrow::Status GetNullsWRT(const std::shared_ptr<arrow::Table>& table, afn::RowWiseStringDF& df, const std::string& column, int32_t max_rows = 256);
    arrow::Status DropNullsWRT(std::shared_ptr<arrow::Table>& table, const std::string& column);
    arrow::Status DropNullsWRTMany(std::shared_ptr<arrow::Table>& table, const std::vector<std::string>& column);
}