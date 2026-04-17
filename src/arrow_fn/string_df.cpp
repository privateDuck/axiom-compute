
#include <arrow/api.h>
#include <sstream>
#include <arrow/compute/api.h>
#include "string_df.hpp"
#include "returnTypes_generated.h"

namespace afn {
    StringCell MakeStringCell(const std::string_view sv) {
        StringCell ps{};

        if (sv.length() < 28) {
            std::memcpy(ps.str, sv.data(), sv.length());
            ps.str[sv.length()] = '\0';
            ps.length = static_cast<int32_t>(sv.length());
        }
        else {
            std::memcpy(ps.str, sv.data(), 24);
            ps.str[24] = '.';
            ps.str[25] = '.';
            ps.str[26] = '.';
            ps.str[27] = '\0';
            ps.length = 27;
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

    void CreateStringDF(flatbuffers::FlatBufferBuilder& builder, const std::shared_ptr<arrow::Array>& array, const std::string& name, const int64_t max_rows)
    {
        const auto rows = std::min(max_rows, array->length());
        // const auto sz_est = std::min(max_rows, rows) * 32;
        // flatbuffers::FlatBufferBuilder builder(sz_est);
        std::vector<flatbuffers::Offset<flatbuffers::String>> name_offsets;
        name_offsets.resize(rows + 1);

        auto cast_result = arrow::compute::Cast(*array, arrow::utf8());
        if (!cast_result.ok()) {
            throw std::runtime_error(cast_result.status().message());
        }

        const auto string_array = std::static_pointer_cast<arrow::StringArray>(cast_result.ValueOrDie());
        name_offsets[0] = builder.CreateString(name);
        for (int64_t i = 0; i < string_array->length(); ++i) {
            if (string_array->IsNull(i)) {
                name_offsets[i + 1] = builder.CreateString("");
            } else {
                const std::string_view sv = string_array->GetView(i);
                name_offsets[i + 1] = builder.CreateString(sv);
            }
        }
        const auto vec = builder.CreateVector(name_offsets);
        const auto stringdf = CreateStringDFResult(builder, vec, static_cast<int32_t>(rows + 1), 1);
        builder.Finish(stringdf);
    }

    void MakeStringDF(flatbuffers::FlatBufferBuilder& builder, const std::shared_ptr<arrow::Table>& table, const int64_t max_rows) {
        const auto rows = std::min(max_rows, table->num_rows());
        const auto cols = table->num_columns();
        const auto max_entries = (rows + 1) * cols;
        std::vector<flatbuffers::Offset<flatbuffers::String>> name_offsets;
        name_offsets.resize(max_entries);
        size_t index = 0;
        size_t col_start_offset = 0;

        const auto schema = table->schema()->fields();
        for (const auto& field : schema) {
            name_offsets[index] = builder.CreateString(field->name());
            ++index;
        }
        col_start_offset += cols;

        for (int c = 0; c < cols; ++c) {
            index = col_start_offset;
            const auto col = table->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto chunked_cast = cast_result.ValueOrDie().chunked_array();
            for (int chk = 0; chk < col->num_chunks(); ++chk) {
                const auto chunk = chunked_cast->chunk(chk);
                const auto string_array = std::static_pointer_cast<arrow::StringArray>(chunk);

                for (int64_t i = 0; i < string_array->length(); ++i) {
                    if (string_array->IsNull(i)) {
                        name_offsets[index] = builder.CreateString("");
                    } else {
                        const std::string_view sv = string_array->GetView(i);
                        name_offsets[index] = builder.CreateString(sv);
                    }
                    index += cols;
                    if (index >= max_entries) break;
                }
            }
            ++col_start_offset;
        }
        const auto vec = builder.CreateVector(name_offsets);
        const auto stringdf = CreateStringDFResult(builder, vec, static_cast<int32_t>(rows + 1), cols);
        builder.Finish(stringdf);
    }

    void CreateStringDF(flatbuffers::FlatBufferBuilder& builder, const std::shared_ptr<arrow::RecordBatch>& batch, const int64_t max_rows) {
        const auto rows = std::min(max_rows, batch->num_rows());
        const auto cols = batch->num_columns();
        const auto max_entries = (rows + 1) * cols;
        std::vector<flatbuffers::Offset<flatbuffers::String>> name_offsets;
        name_offsets.resize(max_entries);

        name_offsets.resize((rows + 1) * cols);
        size_t index = 0;
        size_t col_start_offset = 0;

        const auto schema = batch->schema()->fields();
        for (const auto& field : schema) {
            name_offsets[index] = builder.CreateString(field->name());
            ++index;
        }

        for (int c = 0; c < cols; ++c) {
            index = col_start_offset;
            const auto col = batch->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto string_array = cast_result.ValueOrDie().array_as<arrow::StringArray>();
            for (int64_t i = 0; i < string_array->length(); ++i) {
                if (string_array->IsNull(i)) {
                    name_offsets[index] = builder.CreateString("");
                } else {
                    const std::string_view sv = string_array->GetView(i);
                    name_offsets[index] = builder.CreateString(sv);
                }
                index += cols;
                if (index >= max_entries) break;
            }
            ++col_start_offset;
        }
        const auto vec = builder.CreateVector(name_offsets);
        const auto stringdf = CreateStringDFResult(builder, vec, static_cast<int32_t>(rows + 1), cols);
        builder.Finish(stringdf);
    }

    void RowWiseStringDF::Initialize(const std::shared_ptr<arrow::RecordBatch>& batch) {
        cols = batch->num_columns();
        rows = batch->num_rows();

        data_.resize((rows + 1) * cols);
        size_t index = 0;
        size_t col_start_offset = 0;

        const auto schema = batch->schema()->fields();
        for (const auto& field : schema) {
            data_[index] = MakeStringCell(field->name());
            ++index;
        }

        for (int c = 0; c < cols; ++c) {
            index = col_start_offset;
            const auto col = batch->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto string_array = cast_result.ValueOrDie().array_as<arrow::StringArray>();
            for (int64_t i = 0; i < string_array->length(); ++i) {
                if (string_array->IsNull(i)) {
                    data_[index] = MakeStringCell("");
                } else {
                    const std::string_view sv = string_array->GetView(i);
                    data_[index] = MakeStringCell(sv);
                }
                index += cols;
            }
            ++col_start_offset;
        }
    }

    void RowWiseStringDF::Initialize(const std::shared_ptr<arrow::Table> &table) {
        cols = table->num_columns();
        rows = table->num_rows();

        data_.resize((rows + 1) * cols);
        size_t index = 0;
        size_t col_start_offset = 0;

        const auto schema = table->schema()->fields();
        for (const auto& field : schema) {
            data_[index] = MakeStringCell(field->name());
            ++index;
        }
        col_start_offset += cols;

        for (int c = 0; c < cols; ++c) {
            index = col_start_offset;
            const auto col = table->column(c);
            auto cast_result = arrow::compute::Cast(col, arrow::utf8());
            if (!cast_result.ok()) {
                throw std::runtime_error(cast_result.status().message());
            }
            const auto chunked_cast = cast_result.ValueOrDie().chunked_array();
            for (int chk = 0; chk < col->num_chunks(); ++chk) {
                const auto chunk = chunked_cast->chunk(chk);
                const auto string_array = std::static_pointer_cast<arrow::StringArray>(chunk);

                for (int64_t i = 0; i < string_array->length(); ++i) {
                    if (string_array->IsNull(i)) {
                        data_[index] = MakeStringCell("");
                    } else {
                        const std::string_view sv = string_array->GetView(i);
                        data_[index] = MakeStringCell(sv);
                    }
                    index += cols;
                }
            }
            ++col_start_offset;
        }
    }

    void RowWiseStringDF::Initialize(const std::shared_ptr<arrow::Array> &arr, const std::string &name) {
        cols = 1;
        rows = arr->length();
        data_.resize(rows + 1);

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

    std::string RowWiseStringDF::to_string() const {
        std::ostringstream os;
        for (int32_t i = 0; i < rows; ++i) {
            for (int32_t j = 0; j < cols; ++j) {
                os << data_[i * cols + j].str << " ";
            }
            os << '\n';
        }
        return os.str();
    }
}
