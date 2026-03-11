#pragma once

#include <absl/container/flat_hash_map.h>
#include <algorithm>
#include <bit>          // std::bit_cast  (C++20)
#include <stdexcept>
#include <string>
#include <vector>
#include "TimeConvertions.hpp"
#include "EigenDefinitions.hpp"

namespace df {
    using ColumnType = scripting::fluxpp::Type;

    enum class StringEncodeMethod : uint8_t {
        Ordinal,    // store uint64_t ID directly as double
        OneHot,     // expand to N binary columns (N = # unique values)
    };

    enum class DateTimeEncodeMethod : uint8_t {
        Year, DayOfYear, Month, Day, DayOfWeek, WeekOfYear, Hour, Minute, Second,
    };

    struct ColumnMeta {
        std::string name;
        ColumnType  type = ColumnType::TREAL;
        // size_t      physical_index{};
    };

    namespace detail {
        inline constexpr size_t words_for(size_t n) noexcept {
            return (n + 63u) >> 6u;
        }

        inline bool bm_get(const std::vector<uint64_t>& bm,
                           const size_t col, const size_t wpc, const size_t row) noexcept
        {
            const size_t b = col * wpc * 64u + row;
            return (bm[b >> 6u] >> (b & 63u)) & 1u;
        }

        inline void bm_set(std::vector<uint64_t>& bm,
                           const size_t col, const size_t wpc, const size_t row, const bool v) noexcept
        {
            const size_t b = col * wpc * 64u + row;
            if (v)  bm[b >> 6u] |=  (static_cast<uint64_t>(1) << (b & 63u));
            else    bm[b >> 6u] &= ~(static_cast<uint64_t>(1) << (b & 63u));
        }
    }

    class DataFrame {
    public:
        using Storage = std::vector<double, Eigen::aligned_allocator<double>>;
        using StringMap = absl::flat_hash_map<uint64_t, std::string>;

        DataFrame() = default;

        explicit DataFrame(const size_t rows) : num_rows_(rows) {}

        [[nodiscard]] size_t Rows() const noexcept { return num_rows_; }
        [[nodiscard]] size_t Cols() const noexcept { return schema_.size(); }

        [[nodiscard]] const ColumnMeta& Meta(const size_t ci) const { return schema_.at(ci); }

        [[nodiscard]] bool HasColumn(const std::string& id) const {
            return col_index_.contains(id);
        }

        [[nodiscard]] size_t ColIdx(const std::string& name) const {
            const auto it = col_index_.find(name);
            if (it == col_index_.end())
                throw std::out_of_range("DataFrame: unknown column '" + name + "'");
            return it->second;
        }

        /// `valid` may be empty (all valid) or length num_rows().
        void AddColumnReal(const std::string& name,
                         const std::vector<double>& values,
                         const std::vector<bool>& valid = {})
        {
            _require_size(values.size());
            const size_t ci = _grow(name, ColumnType::TREAL);
            std::ranges::copy(values, _col_ptr(ci));
            _init_validity(ci, valid);
        }

        void AddColumnDatetime(const std::string& name,
                             const std::vector<uint64_t>& values,
                             const std::vector<bool>& valid = {})
        {
            _require_size(values.size());
            const size_t ci = _grow(name, ColumnType::TTIMESTAMP);
            double* dst = _col_ptr(ci);
            for (size_t i = 0; i < values.size(); ++i)
                dst[i] = std::bit_cast<double>(values[i]);
            _init_validity(ci, valid);
        }

        void AddColumnBool(const std::string& name,
                             const std::vector<bool>& values,
                             const std::vector<bool>& valid = {})
        {
            _require_size(values.size());
            size_t ci = _grow(name, ColumnType::TBOOL);
            double* dst = _col_ptr(ci);
            for (size_t i = 0; i < values.size(); ++i) {
                uint64_t u = values[i] ? 1u : 0u;
                dst[i] = std::bit_cast<double>(u);
            }
            _init_validity(ci, valid);
        }

        void AddColumnString(const std::string& name,
                               const std::vector<std::string>& values,
                               const std::vector<bool>& valid = {})
        {
            _require_size(values.size());
            const size_t ci = _grow(name, ColumnType::TSTRING);
            double* dst = _col_ptr(ci);

            StringMap& dict = string_dicts_[ci];
            absl::flat_hash_map<std::string, uint64_t> rev;   // dedup cache
            uint64_t next_id = 0;

            for (size_t i = 0; i < values.size(); ++i) {
                auto [it, inserted] = rev.emplace(values[i], next_id);
                if (inserted) {
                    dict[next_id] = values[i];
                    ++next_id;
                }
                dst[i] = std::bit_cast<double>(it->second);
            }
            _init_validity(ci, valid);
        }

        [[nodiscard]] bool IsValid(const size_t col, const size_t row) const {
            _chk(col, row);
            return detail::bm_get(validity_, col, wpc(), row);
        }

        void SetValid(const size_t col, const size_t row, const bool v) {
            _chk(col, row);
            detail::bm_set(validity_, col, wpc(), row, v);
        }

        [[nodiscard]] double GetReal(const size_t col, const size_t row) const {
            _tchk(col, row, ColumnType::TREAL);
            return data_[col * num_rows_ + row];
        }

        [[nodiscard]] uint64_t GetDatetime(const size_t col, const size_t row) const {
            _tchk(col, row, ColumnType::TTIMESTAMP);
            return std::bit_cast<uint64_t>(data_[col * num_rows_ + row]);
        }

        [[nodiscard]] bool GetBool(const size_t col, const size_t row) const {
            _tchk(col, row, ColumnType::TBOOL);
            return std::bit_cast<uint64_t>(data_[col * num_rows_ + row]) != 0u;
        }

        [[nodiscard]] const std::string& GetString(const size_t col, const size_t row) const {
            _tchk(col, row, ColumnType::TSTRING);
            const auto id = std::bit_cast<uint64_t>(data_[col * num_rows_ + row]);
            return string_dicts_.at(col).at(id);
        }

        void SetReal(const size_t col, const size_t row, const double v) {
            _tchk(col, row, ColumnType::TREAL);
            data_[col * num_rows_ + row] = v;
        }

        void SetDatetime(const size_t col, const size_t row, const uint64_t timestamp) {
            _tchk(col, row, ColumnType::TTIMESTAMP);
            data_[col * num_rows_ + row] = std::bit_cast<double>(timestamp);
        }

        void SetBool(const size_t col, const size_t row, const bool v) {
            _tchk(col, row, ColumnType::TBOOL);
            uint64_t u = v ? 1u : 0u;
            data_[col * num_rows_ + row] = std::bit_cast<double>(u);
        }

        // This adds an unknown entry. Should be cautious
        void SetString(const size_t col, const size_t row, const std::string& s) {
            _tchk(col, row, ColumnType::TSTRING);
            auto& dict = string_dicts_.at(col);
            // Search existing entries
            for (auto& [id, str] : dict) {
                if (str == s) {
                    data_[col * num_rows_ + row] = std::bit_cast<double>(id);
                    return;
                }
            }

            // This adds an unknown entry. Should be cautious
            const auto new_id = static_cast<uint64_t>(dict.size());
            dict[new_id] = s;
            data_[col * num_rows_ + row] = std::bit_cast<double>(new_id);
        }

        Eigen::Map<Eigen::VectorXd> ColumnView(const size_t col) {
            _type_only_chk(col, ColumnType::TREAL);
            return {_col_ptr(col), static_cast<Eigen::Index>(num_rows_)};
        }

        [[nodiscard]] Eigen::Map<const Eigen::VectorXd> ColumnView(const size_t col) const {
            _type_only_chk(col, ColumnType::TREAL);
            return {data_.data() + col * num_rows_, static_cast<Eigen::Index>(num_rows_)};
        }

        Eigen::Map<Eigen::VectorXd> ColumnView(const std::string& n) { return ColumnView(ColIdx(n)); }

        [[nodiscard]] Eigen::Map<const Eigen::VectorXd> ColumnView(const std::string& n) const { return ColumnView(ColIdx(n)); }

        [[nodiscard]] DataFrame clone() const {
            DataFrame out;
            out.num_rows_     = num_rows_;
            out.data_         = data_;
            out.validity_     = validity_;
            out.schema_       = schema_;
            out.col_index_    = col_index_;
            out.string_dicts_ = string_dicts_;
            return out;
        }

        struct ColumnCopy {
            std::vector<double> data;    // length == original num_rows()
            std::vector<bool>   valid;   // length == original num_rows()
            ColumnMeta          meta;
        };

        [[nodiscard]] ColumnCopy ExtractColumn(size_t col) const {
            _col_chk(col);
            ColumnCopy cc;
            cc.meta = schema_[col];
            cc.data.assign(data_.data() + col * num_rows_,
                           data_.data() + (col + 1) * num_rows_);
            cc.valid.resize(num_rows_);
            for (size_t r = 0; r < num_rows_; ++r)
                cc.valid[r] = detail::bm_get(validity_, col, wpc(), r);
            return cc;
        }

        [[nodiscard]] ColumnCopy ExtractColumn(const std::string& name) const {
            return ExtractColumn(ColIdx(name));
        }

        [[nodiscard]] EigenRowAlignedDoubleMat ToMatrix() const {
            const auto R = static_cast<Eigen::Index>(num_rows_);
            const auto C = static_cast<Eigen::Index>(schema_.size());
            EigenRowAlignedDoubleMat M(R, C);
            for (size_t c = 0; c < schema_.size(); ++c)
                for (size_t r = 0; r < num_rows_; ++r)
                    M(static_cast<Eigen::Index>(r),
                      static_cast<Eigen::Index>(c)) = data_[c * num_rows_ + r];
            return M;
        }

        void DeleteColumn(size_t col) {
            _col_chk(col);
            const size_t ncols    = schema_.size();
            const size_t old_wpc  = wpc();

            // Compact backing store
            Storage nd((ncols - 1) * num_rows_);
            for (size_t c = 0, dc = 0; c < ncols; ++c) {
                if (c == col) continue;
                std::copy(data_.data() + c * num_rows_,
                          data_.data() + (c + 1) * num_rows_,
                          nd.data() + dc * num_rows_);
                ++dc;
            }
            data_ = std::move(nd);

            // Compact validity bitmap  (wpc unchanged after DeleteColumn)
            std::vector<uint64_t> nbm((ncols - 1) * old_wpc, 0u);
            for (size_t c = 0, dc = 0; c < ncols; ++c) {
                if (c == col) continue;
                for (size_t r = 0; r < num_rows_; ++r)
                    if (detail::bm_get(validity_, c, old_wpc, r))
                        detail::bm_set(nbm, dc, old_wpc, r, true);
                ++dc;
            }
            validity_ = std::move(nbm);

            // String dictionaries: drop deleted, re-key shifted cols
            string_dicts_.erase(col);
            {
                absl::flat_hash_map<size_t, StringMap> tmp;
                for (auto& [k, v] : string_dicts_)
                    tmp[k > col ? k - 1 : k] = std::move(v);
                string_dicts_ = std::move(tmp);
            }

            // 4. Schema & reverse index
            schema_.erase(schema_.begin() + static_cast<ptrdiff_t>(col));
            col_index_.clear();
            for (size_t i = 0; i < schema_.size(); ++i) {
                //schema_[i].physical_index = i;
                col_index_[schema_[i].name] = i;
            }
        }

        void DeleteColumn(const std::string& name) { DeleteColumn(ColIdx(name)); }

        // Delete every element with value 1.0
        void DeleteRowsMask(const Eigen::VectorXd& mask) {
            if (static_cast<size_t>(mask.size()) != num_rows_)
                throw std::invalid_argument("delete_rows_mask: mask length mismatch");
            std::vector<size_t> del;
            del.reserve(static_cast<size_t>(mask.sum()));
            for (Eigen::Index i = 0; i < mask.size(); ++i)
                if (mask[i] == 1.0)
                    del.emplace_back(static_cast<size_t>(i));
            _erase_rows(del);   // already sorted (ascending scan)
        }

        void DeleteRowsMask(const Eigen::VectorXi& mask) {
            if (static_cast<size_t>(mask.size()) != num_rows_)
                throw std::invalid_argument("delete_rows_mask: mask length mismatch");
            std::vector<size_t> del;
            del.reserve(static_cast<size_t>(mask.sum()));
            for (Eigen::Index i = 0; i < mask.size(); ++i)
                if (mask[i] == 1.0)
                    del.emplace_back(static_cast<size_t>(i));
            _erase_rows(del);   // already sorted (ascending scan)
        }

        // Delete rows with given indices
        void DeleteRowsIndices(std::vector<size_t> indices) {
            std::ranges::sort(indices);
            indices.erase(std::ranges::unique(indices).begin(),
                          indices.end());
            _erase_rows(indices);
        }

        [[nodiscard]] EigenRowAlignedDoubleMat encode_frame(StringEncodeMethod   str_enc, DateTimeEncodeMethod dt_enc) const
        {
            // Pass 1: compute output column count
            size_t out_cols = 0;
            for (size_t c = 0; c < schema_.size(); ++c) {
                if (schema_[c].type == ColumnType::TSTRING &&
                    str_enc == StringEncodeMethod::OneHot)
                {
                    auto it = string_dicts_.find(c);
                    out_cols += (it != string_dicts_.end())
                                ? it->second.size() : 0;
                } else {
                    ++out_cols;
                }
            }

            auto ei = [](const size_t x) { return static_cast<Eigen::Index>(x); };
            Eigen::MatrixXd M = Eigen::MatrixXd::Zero(ei(num_rows_), ei(out_cols));

            // Pass 2: fill
            size_t oc = 0;
            for (size_t c = 0; c < schema_.size(); ++c) {
                switch (schema_[c].type) {

                    case ColumnType::TREAL:
                        for (size_t r = 0; r < num_rows_; ++r)
                            M(ei(r), ei(oc)) = data_[c * num_rows_ + r];
                        ++oc;
                        break;

                    case ColumnType::TBOOL:
                        for (size_t r = 0; r < num_rows_; ++r) {
                            const auto v = std::bit_cast<uint64_t>(data_[c * num_rows_ + r]);
                            M(ei(r), ei(oc)) = (v != 0u) ? 1.0 : 0.0;
                        }
                        ++oc;
                        break;

                    case ColumnType::TTIMESTAMP:
                        for (size_t r = 0; r < num_rows_; ++r) {
                            auto ep = std::bit_cast<uint64_t>(data_[c * num_rows_ + r]);
                            M(ei(r), ei(oc)) = _dt_field(ep, dt_enc);
                        }
                        ++oc;
                        break;

                    case ColumnType::TSTRING:
                        if (str_enc == StringEncodeMethod::Ordinal) {
                            for (size_t r = 0; r < num_rows_; ++r) {
                                const auto id = std::bit_cast<uint64_t>(
                                                  data_[c * num_rows_ + r]);
                                M(ei(r), ei(oc)) = static_cast<double>(id);
                            }
                            ++oc;
                        } else {
                            // One-hot: stable ordering by sorted ID
                            const auto& dict = string_dicts_.at(c);
                            std::vector<uint64_t> ids;
                            ids.reserve(dict.size());
                            for (const auto &id: dict | std::views::keys) ids.push_back(id);
                            std::ranges::sort(ids);

                            absl::flat_hash_map<uint64_t, size_t> id_off;
                            for (size_t i = 0; i < ids.size(); ++i)
                                id_off[ids[i]] = i;

                            for (size_t r = 0; r < num_rows_; ++r) {
                                const auto id = std::bit_cast<uint64_t>(data_[c * num_rows_ + r]);
                                M(ei(r), ei(oc + id_off.at(id))) = 1.0;
                            }
                            oc += ids.size();
                        }
                        break;
                    case scripting::fluxpp::Type::TNULL:
                        break;
                }
            }
            return M;
        }

        [[nodiscard]] std::string PrintSchema() const {
            static const char* names[] = {"Real","DateTime","Boolean","String"};
            std::string str = "";
            for (size_t i = 0; i < schema_.size(); ++i) {
                const auto&[name, type] = schema_[i];
                str += std::format("[{0}] {1:<24}  {2:<10}  phys={3}\n",
                       i, name,
                       names[static_cast<int>(type)],
                       i);
            }
            return str;
        }

        /// Access the string dictionary for a String column (read-only).
        [[nodiscard]] const StringMap& string_dict(const size_t col) const {
            _type_only_chk(col, ColumnType::TSTRING);
            return string_dicts_.at(col);
        }

    private:
        size_t  num_rows_  = 0;
        Storage data_;
        std::vector<uint64_t>  validity_;
        std::vector<ColumnMeta> schema_;
        absl::flat_hash_map<std::string, size_t> col_index_;
        absl::flat_hash_map<size_t, StringMap>   string_dicts_;

        [[nodiscard]] size_t wpc() const noexcept { return detail::words_for(num_rows_); }

        double* _col_ptr(const size_t col) noexcept {
            return data_.data() + col * num_rows_;
        }

        /// Ensure incoming length matches (or fix num_rows_ on the very first column).
        void _require_size(size_t n) {
            if (schema_.empty()) {
                num_rows_ = n;
            } else if (n != num_rows_) {
                throw std::invalid_argument(
                    "Column length " + std::to_string(n) +
                    " does not match num_rows=" + std::to_string(num_rows_));
            }
        }

        /// Append one column slot: grow backing store + bitmap, register metadata.
        /// Returns the new physical column index.
        size_t _grow(const std::string& name, const ColumnType type) {
            if (col_index_.contains(name))
                throw std::invalid_argument("Duplicate column name: " + name);

            const size_t ci = schema_.size();

            // Backing store: append num_rows_ zero-initialized doubles
            Storage nd((ci + 1) * num_rows_, 0.0);
            std::ranges::copy(data_, nd.begin());
            data_ = std::move(nd);

            // Validity bitmap: append one word-aligned block (resize preserves old bits)
            validity_.resize((ci + 1) * wpc(), 0u);

            schema_.push_back({name, type});
            col_index_[name] = ci;
            return ci;
        }

        void _init_validity(const size_t col, const std::vector<bool>& valid) {
            const bool all_valid = valid.empty();
            for (size_t r = 0; r < num_rows_; ++r)
                detail::bm_set(validity_, col, wpc(), r,
                               all_valid || valid[r]);
        }

        /// Core row-deletion: `to_del` must be sorted, unique, and in-range.
        void _erase_rows(const std::vector<size_t>& to_del) {
            if (to_del.empty()) return;
            for (const size_t idx : to_del)
                if (idx >= num_rows_)
                    throw std::out_of_range("Row index out of range in delete");

            const size_t new_rows = num_rows_ - to_del.size();
            const size_t ncols    = schema_.size();
            const size_t old_wpc  = wpc();


            struct Chunk {size_t start, len;};
            std::vector<Chunk> chunks_to_keep;
            size_t last_idx = 0;
            for (const auto del_idx : to_del) {
                if (del_idx > last_idx)
                    chunks_to_keep.emplace_back(last_idx, del_idx - last_idx);
                last_idx = del_idx + 1;
            }
            if (last_idx < num_rows_) {
                chunks_to_keep.emplace_back(last_idx, num_rows_ - last_idx);
            }
            // Compact data column by column
            Storage nd(ncols * new_rows);
            for (size_t c = 0; c < ncols; ++c) {
                const double* src = data_.data() + c * num_rows_;
                double* dst = nd.data() + c * new_rows;
                size_t offset = 0;
                for (const auto& chunk: chunks_to_keep) {
                    std::copy_n(src + chunk.start, chunk.len, dst + offset);
                    offset += chunk.len;
                }
            }

            // Compact bitmap
            const size_t new_wpc = detail::words_for(new_rows);
            std::vector<uint64_t> nbm(ncols * new_wpc, 0u);
            for (size_t c = 0; c < ncols; ++c) {
                size_t di = 0;
                for (const auto& chunk : chunks_to_keep) {
                    for (size_t i = 0; i < chunk.len; ++i) {
                        if (detail::bm_get(validity_, c, old_wpc, chunk.start + i))
                            detail::bm_set(nbm, c, new_wpc, di, true);
                        ++di;
                    }
                }
            }

            data_     = std::move(nd);
            validity_ = std::move(nbm);
            num_rows_ = new_rows;
        }

        void _col_chk(const size_t col) const {
            if (col >= schema_.size())
                throw std::out_of_range("Column index " + std::to_string(col) + " out of range");
        }
        void _chk(const size_t col, const size_t row) const {
            _col_chk(col);
            if (row >= num_rows_)
                throw std::out_of_range("Row index " + std::to_string(row) + " out of range");
        }
        void _type_only_chk(const size_t col, const ColumnType t) const {
            _col_chk(col);
            if (schema_[col].type != t)
                throw std::runtime_error("Type mismatch for column '" + schema_[col].name + "'");
        }
        void _tchk(const size_t col, const size_t row, const ColumnType t) const {
            _chk(col, row);
            if (schema_[col].type != t)
                throw std::runtime_error("Type mismatch for column '" + schema_[col].name + "'");
        }

        static double _dt_field(const uint64_t ts, DateTimeEncodeMethod m) noexcept
        {
            switch (m) {
                case DateTimeEncodeMethod::Year:
                    return get_year(ts);
                case DateTimeEncodeMethod::DayOfYear:
                    return get_day_of_year(ts);
                case DateTimeEncodeMethod::Month:
                    return get_month(ts);
                case DateTimeEncodeMethod::Day:
                    return get_day(ts);
                case DateTimeEncodeMethod::DayOfWeek:
                    return get_day_of_week(ts);
                case DateTimeEncodeMethod::WeekOfYear:
                    return get_week_of_year(ts);
                case DateTimeEncodeMethod::Hour:
                    return get_hour(ts);
                case DateTimeEncodeMethod::Minute:
                    return get_minute(ts);
                case DateTimeEncodeMethod::Second:
                    return get_second(ts);
            }
            return static_cast<double>(ts);
        }
    };
}
