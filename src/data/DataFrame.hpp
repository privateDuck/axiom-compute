#pragma once


#include <Eigen/Eigen>
#include <duckdb/duckdb.h>
#include <type_traits>


enum class ColType { INT64, FLOAT, VARCHAR, UNKNOWN };

// Base class for runtime polymorphism
class IColumn {
public:
    virtual ~IColumn() = default;
    virtual ColType GetType() const = 0;
    virtual size_t Size() const = 0;
    virtual void Reserve(size_t capacity) = 0;

    // Helper to identify data types for C-API
    static ColType FromDuckType(duckdb_type type) {
        switch (type) {
        case DUCKDB_TYPE_BIGINT: return ColType::INT64;
        case DUCKDB_TYPE_FLOAT: return ColType::FLOAT;
        case DUCKDB_TYPE_VARCHAR: return ColType::VARCHAR;
        default: return ColType::UNKNOWN;
        }
    }
};

// Templated Concrete Column
// Stores data contiguously in std::vector
template <typename T>
class Column : public IColumn {
    std::vector<T> data_;
    ColType type_id_;

public:
    Column(ColType id) : type_id_(id) {}

    std::vector<T>& GetData() { return data_; }
    std::span<const T> GetSpan() const { return data_; }

    ColType GetType() const override { return type_id_; }
    size_t Size() const override { return data_.size(); }
    void Reserve(size_t capacity) override { data_.reserve(capacity); }

    void Append(const T& val) { data_.push_back(val); }

    void AppendBlock(const T* source, size_t count) {
        data_.insert(data_.end(), source, source + count);
    }

    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>> GetEigenMap() {
        if (std::is_floating_point<T>(T))
            return Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>>(data_.data(), data_.size());
		else
			throw std::runtime_error("Eigen Map only supported for floating point types");
    }

};


class DataFrame {
    std::vector<std::string> names_;
    std::vector<std::shared_ptr<IColumn>> columns_;
    size_t row_count_ = 0;

public:
    DataFrame() = default;

    void AddColumn(const std::string& name, std::shared_ptr<IColumn> col) {
        // Ensure new column matches existing row count (simple validation)
        if (row_count_ > 0 && col->Size() != row_count_) {
            // Logic to resize/fill could go here. For now, strict check.
            if (col->Size() == 0) col->Reserve(row_count_); // Allow empty init
        }
        names_.push_back(name);
        columns_.push_back(std::move(col));
        if (columns_.size() == 1) row_count_ = columns_[0]->Size();
    }

    void DropColumn(const std::string& name) {
        auto it = std::find(names_.begin(), names_.end(), name);
        if (it != names_.end()) {
            size_t idx = std::distance(names_.begin(), it);
            names_.erase(it);
            columns_.erase(columns_.begin() + idx);
        }
    }

    // Templated access to column data
    template <typename T>
    std::vector<T>& GetColumnData(size_t index) {
        if (index >= columns_.size()) throw std::out_of_range("Column index out of range");
        auto casted = std::dynamic_pointer_cast<Column<T>>(columns_[index]);
        if (!casted) throw std::runtime_error("Type mismatch in GetColumnData");
        return casted->GetData();
    }

    // Metadata access
    size_t RowCount() const { return columns_.empty() ? 0 : columns_[0]->Size(); }
    size_t ColCount() const { return columns_.size(); }
    const std::string& GetName(size_t i) const { return names_[i]; }
    const std::shared_ptr<IColumn>& GetColumn(size_t i) const { return columns_[i]; }

	// Makes a deep copy of the DataFrame
    DataFrame Clone() const {
        DataFrame copy;
        for (size_t i = 0; i < columns_.size(); ++i) {
            const auto& col = columns_[i];
            std::shared_ptr<IColumn> col_copy;
            switch (col->GetType()) {
            case ColType::INT64: {
                auto* typed_col = static_cast<Column<int64_t>*>(col.get());
                auto new_col = std::make_shared<Column<int64_t>>(ColType::INT64);
                new_col->AppendBlock(typed_col->GetData().data(), typed_col->Size());
                col_copy = new_col;
                break;
            }
            case ColType::FLOAT: {
                auto* typed_col = static_cast<Column<float>*>(col.get());
                auto new_col = std::make_shared<Column<float>>(ColType::FLOAT);
                new_col->AppendBlock(typed_col->GetData().data(), typed_col->Size());
                col_copy = new_col;
                break;
            }
            case ColType::VARCHAR: {
                auto* typed_col = static_cast<Column<std::string>*>(col.get());
                auto new_col = std::make_shared<Column<std::string>>(ColType::VARCHAR);
                new_col->AppendBlock(typed_col->GetData().data(), typed_col->Size());
                col_copy = new_col;
                break;
            }
            default:
                throw std::runtime_error("Unsupported column type in clone");
            }
            copy.AddColumn(names_[i], col_copy);
        }
		return copy;
    }
};