#pragma once

#include "interop_types.h"
#include <string>
#include <vector>
#include <cstring>


namespace top {
    class ResultBuilder {
    public:
        ResultBuilder() = default;

        CValue* AllocValues(const size_t n) {
            auto* p = new CValue[n]{};
            owned_value_arrays_.push_back(p);
            return p;
        }

        CString MakeString(const std::string& str) {
            auto* buf = new char[str.size() + 1];
            std::memcpy(buf, str.data(), str.size() + 1);
            owned_strings_.push_back(buf);
            return CString{buf, str.size()};
        }

        CString MakeString(const std::string_view str) {
            auto* buf = new char[str.size() + 1];
            std::memcpy(buf, str.data(), str.size() + 1);
            owned_strings_.push_back(buf);
            return CString{buf, str.size()};
        }

        static CValue MakeNull() { return CValue{ C_VALUE_NULL }; }
        static CValue MakeBool(const bool v) { CValue r{C_VALUE_BOOL};   r.bool_val   = v; return r; }
        CValue MakeInt(int64_t v) { CValue r{C_VALUE_INT64};  r.int64_val  = v; return r; }
        CValue MakeFloat(double v){ CValue r{C_VALUE_FLOAT64};r.float64_val= v; return r; }
        CValue MakeStr(const std::string& s) {
            CValue r{C_VALUE_STRING}; r.string_val = MakeString(s); return r;
        }
        CValue MakeStr(const std::string_view s) {
            CValue r{C_VALUE_STRING}; r.string_val = MakeString(s); return r;
        }

        CValue MakeList(const std::vector<CValue>& items) {
            CValue r{C_VALUE_LIST};
            r.list_val.count = items.size();
            r.list_val.items = AllocValues(items.size());
            std::ranges::copy(items, r.list_val.items);
            return r;
        }

        CValue MakeMap(const std::vector<std::pair<std::string, CValue>> &kv) {
            CValue r{C_VALUE_MAP};
            r.map_val.count  = kv.size();
            r.map_val.keys   = new CString[kv.size()];
            r.map_val.values = AllocValues(kv.size());
            owned_key_arrays_.push_back(r.map_val.keys);
            for (size_t i = 0; i < kv.size(); ++i) {
                r.map_val.keys[i]   = MakeString(kv[i].first);
                r.map_val.values[i] = kv[i].second;
            }
            return r;
        }

        // Add a typed column to a dataframe value
        // T must match col_type
        template<typename T>
        CColumn MakeColumn(const std::string& name, const CColumnType col_type, std::vector<T> data, std::vector<bool> nulls = {}) {
            T* buf = new T[data.size()];
            std::copy(data.begin(), data.end(), buf);
            owned_raw_.push_back(reinterpret_cast<void*>(buf));

            bool* mask = nullptr;
            if (!nulls.empty()) {
                mask = new bool[nulls.size()];
                for (size_t i = 0; i < nulls.size(); ++i) mask[i] = nulls[i];
                owned_raw_.push_back(reinterpret_cast<void*>(mask));
            }
            return CColumn{ MakeString(name), col_type, buf, mask, data.size() };
        }

        CValue MakeDataframe(std::vector<CColumn> cols, const size_t row_count) {
            CValue r{C_VALUE_DATAFRAME};
            auto* col_buf = new CColumn[cols.size()];
            std::ranges::copy(cols, col_buf);
            owned_col_arrays_.push_back(col_buf);
            r.dataframe_val = CDataFrame{ col_buf, cols.size(), row_count };
            return r;
        }

        ~ResultBuilder() {
            for (auto* p : owned_value_arrays_) delete[] p;
            for (auto* p : owned_key_arrays_)  delete[] p;
            for (auto* p : owned_col_arrays_)  delete[] p;
            for (auto* p : owned_strings_)     delete[] p;
            for (auto* p : owned_raw_)         ::operator delete(p);
        }

        ResultBuilder(const ResultBuilder&) = delete;
        ResultBuilder& operator=(const ResultBuilder&) = delete;
    private:
        std::vector<CValue*>  owned_value_arrays_;
        std::vector<CString*> owned_key_arrays_;
        std::vector<CColumn*> owned_col_arrays_;
        std::vector<char*>    owned_strings_;
        std::vector<void*>    owned_raw_;
    };
}