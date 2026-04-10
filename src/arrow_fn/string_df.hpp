#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <arrow/api.h>

namespace afn {

    struct alignas(8) StringCell {
        char str[20];
        int32_t length;
    };

    struct StringColumn {
        std::string name;
        std::vector<StringCell> data;
        StringColumn(const std::string &name, std::vector<StringCell>&& data) : name(name), data(std::move(data)) {}
    };

    class StringDF {
    public:
        StringDF() = default;
        void AddColumnFromArrowArray(const std::shared_ptr<arrow::Array> &array, const std::string& name);
        static StringDF FromArrowTable(const std::shared_ptr<arrow::Table> &table);
    private:
        std::unordered_map<std::string, uint32_t> col_idx;
        std::vector<StringColumn> columns;
    };

    class RowWiseStringDF {
    public:
        explicit RowWiseStringDF(const std::shared_ptr<arrow::Array>& arr, const std::string& name = "Column Data");
        explicit RowWiseStringDF(const std::shared_ptr<arrow::Table>& table);
        explicit RowWiseStringDF(const std::shared_ptr<arrow::RecordBatch>& batch);
    private:
        std::vector<StringCell> data_;
        int32_t rows;
        int32_t cols;
    };
}
