#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <arrow/api.h>

namespace afn {

    struct alignas(8) StringCell {
        char str[28];
        int32_t length;
    };

    class RowWiseStringDF {
    public:
        RowWiseStringDF() : rows(0), cols(0) {}
        void Initialize(const std::shared_ptr<arrow::RecordBatch>& batch);
        void Initialize(const std::shared_ptr<arrow::Table>& table);
        void Initialize(const std::shared_ptr<arrow::Array>& arr, const std::string& name = "Column Data");
        [[nodiscard]] std::string to_string() const;
    private:
        std::vector<StringCell> data_;
        int32_t rows;
        int32_t cols;
    };
}
