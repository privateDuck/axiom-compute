
#include <arrow/api.h>
#include <arrow/compute/api.h>
#include "string_df.hpp"

namespace afn {
    StringCell MakeStringCell(const std::string_view sv) {
        StringCell ps;

        if (sv.length() < 20) {
            std::memcpy(ps.str, sv.data(), sv.length());
            ps.str[sv.length()] = '\0';
            ps.length = static_cast<int32_t>(sv.length());
        }
        else {
            std::memcpy(ps.str, sv.data(), 16);
            ps.str[16] = '.';
            ps.str[17] = '.';
            ps.str[18] = '.';
            ps.str[19] = '\0';
            ps.length = 19;
        }

        return ps;
    }


    arrow::Result<std::vector<StringCell>> ConvertToPartialStrings(const std::shared_ptr<arrow::Array>& input_array) {
        std::vector<StringCell> result;
        result.reserve(input_array->length());

        auto cast_result = arrow::compute::Cast(*input_array, arrow::utf8());
        if (!cast_result.ok()) {
            return cast_result.status();
        }

        const auto string_array = std::static_pointer_cast<arrow::StringArray>(cast_result.ValueOrDie());

        for (int64_t i = 0; i < string_array->length(); ++i) {
            if (string_array->IsNull(i)) {
                result.push_back(MakeStringCell(""));
            } else {
                const std::string_view sv = string_array->GetView(i);
                result.push_back(MakeStringCell(sv));
            }
        }

        return result;
    }

    void StringDF::AddColumnFromArrowArray(const std::shared_ptr<arrow::Array> &array, const std::string &name) {
        auto vector = ConvertToPartialStrings(array);
        if (!vector.ok()) {
            return;
        }
        columns.emplace_back(name, std::move(vector.ValueOrDie()));
        col_idx.insert_or_assign(name, columns.size() - 1);
    }

    StringDF StringDF::FromArrowTable(const std::shared_ptr<arrow::Table> &table) {
        StringDF result;
        for (size_t i = 0; i < table->num_columns(); ++i) {
            const auto field = table->field(i);
            result.AddColumnFromArrowArray(table->column(i)->chunk(0), field->name());
        }
        return result;
    }


    RowWiseStringDF::RowWiseStringDF(const std::shared_ptr<arrow::Array> &arr, const std::string& name) {
        cols = 1;
        rows = arr->length();
        data_.reserve(rows + 1);

        auto cast_result = arrow::compute::Cast(*arr, arrow::utf8());
        if (!cast_result.ok()) {
            throw std::runtime_error(cast_result.status().message());
        }

        const auto string_array = std::static_pointer_cast<arrow::StringArray>(cast_result.ValueOrDie());
        data_[0] = MakeStringCell(name);
        for (int64_t i = 0; i < string_array->length(); ++i) {
            if (string_array->IsNull(i)) {
                data_[i + 1] = MakeStringCell("");
            } else {
                const std::string_view sv = string_array->GetView(i);
                data_[i + 1] = MakeStringCell(sv);
            }
        }
    }

    RowWiseStringDF::RowWiseStringDF(const std::shared_ptr<arrow::Table> &table) {
        cols = table->num_columns();
        rows = table->num_rows();
        std::vector<StringCell> temp;
        data_.reserve(rows * cols);
        temp.reserve((rows + 1) * cols);
        size_t index = 0;
        for (size_t c = 0; c < cols; ++c) {
            const auto col = table->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto chunked_cast = cast_result.ValueOrDie().chunked_array();
            for (size_t chk = 0; chk < col->num_chunks(); ++chk) {
                const auto chunk = chunked_cast->chunk(chk);
                const auto string_array = std::static_pointer_cast<arrow::StringArray>(chunk);

                for (int64_t i = 0; i < string_array->length(); ++i) {
                    if (string_array->IsNull(i)) {
                        temp[index] = MakeStringCell("");
                    } else {
                        const std::string_view sv = string_array->GetView(i);
                        temp[index] = MakeStringCell(sv);
                    }
                    ++index;
                }
            }
        }

        index = 0;
        const auto schema = table->schema()->fields();
        for (const auto field : schema) {
            data_[index] = MakeStringCell(field->name());
            ++index;
        }
        for (size_t c = 0; c < cols; ++c) {
            for (size_t r = 0; r < rows; ++r) {
                data_[index] = temp[c * rows + r];
                ++index;
            }
        }
    }

    RowWiseStringDF::RowWiseStringDF(const std::shared_ptr<arrow::RecordBatch> &batch) {
        cols = batch->num_columns();
        rows = batch->num_rows();
        std::vector<StringCell> temp;
        data_.reserve(rows * cols);
        temp.reserve((rows + 1) * cols);
        size_t index = 0;
        for (size_t c = 0; c < cols; ++c) {
            const auto col = batch->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto string_array = cast_result.ValueOrDie().array_as<arrow::StringArray>();
            for (int64_t i = 0; i < string_array->length(); ++i) {
                if (string_array->IsNull(i)) {
                    temp[index] = MakeStringCell("");
                } else {
                    const std::string_view sv = string_array->GetView(i);
                    temp[index] = MakeStringCell(sv);
                }
                ++index;
            }
        }

        index = 0;
        const auto schema = batch->schema()->fields();
        for (const auto field : schema) {
            data_[index] = MakeStringCell(field->name());
            ++index;
        }
        for (size_t c = 0; c < cols; ++c) {
            for (size_t r = 0; r < rows; ++r) {
                data_[index] = temp[c * rows + r];
                ++index;
            }
        }
    }
}
