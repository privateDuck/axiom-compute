#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "../exec/ExprEngine/types.hpp"
#include "ref.hpp"

namespace exec {

    class ComputeColumn {
    public:
        ComputeColumn(const std::string &name, const expr::Type type)
            : name(name),
              type(type), col_idx() {
        }

        [[nodiscard]] expr::Type getType() const { return type; }
        [[nodiscard]] std::string_view getName() const { return name; }
    private:
        std::string name;
        expr::Type type;
        uint32_t col_idx;
    };

    // Schema container for constructing the compute graph
    class ComputeSchema {
    public:
        [[nodiscard]] bool hasColumn(const std::string &name) const {
            return col_idx.contains(name);
        }
        [[nodiscard]] const ComputeColumn& getColumnSchema(const std::string &name) const {
            if (!hasColumn(name)) {
                throw std::runtime_error("Column not found in schema: " + name);
            }
            return columns.at(col_idx.at(name));
        }
    private:
        std::vector<ComputeColumn> columns;
        std::vector<BoxRef<uint32_t>> column_ptr;
        std::unordered_map<std::string, uint32_t> col_idx;
    };

}