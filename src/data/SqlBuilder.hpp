#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string_view>
#include <optional>

// ==========================================
// 1. Select Builder
// ==========================================

class SelectBuilder {
private:
    std::vector<std::string> columns;
    std::string fromTable;
    std::vector<std::string> joins;
    std::string whereClause;

public:
    // 1. SELECT: Variadic template to accept any number of raw string columns
    // Usage: .Select("age", "name", "salary * 12 AS annual")
    template<typename... Args>
    SelectBuilder& Select(Args... args) {
        (columns.push_back(std::string(args)), ...);
        return *this;
    }

    // Helper to add a specific column with an alias cleanly
    // Usage: .Col("age - MAX(age)", "ageMinus")
    SelectBuilder& Col(std::string_view expression, std::string_view alias = "") {
        if (alias.empty()) {
            columns.push_back(std::string(expression));
        }
        else {
            columns.push_back(std::string(expression) + " AS " + std::string(alias));
        }
        return *this;
    }

    // 2. FROM
    SelectBuilder& From(std::string_view table) {
        fromTable = table;
        return *this;
    }

    // 3. JOINS
    // usage: .Join("orders", "users.id = orders.user_id", "LEFT")
    SelectBuilder& Join(std::string_view table, std::string_view onCondition, std::string_view type = "INNER") {
        std::ostringstream ss;
        ss << " " << type << " JOIN " << table << " ON " << onCondition;
        joins.push_back(ss.str());
        return *this;
    }

    // 4. WHERE
    SelectBuilder& Where(std::string_view expression) {
        whereClause = expression;
        return *this;
    }

    // Generate the Final SQL
    std::string get() const {
        if (fromTable.empty()) return ""; // Minimal validation

        std::ostringstream sql;
        sql << "SELECT ";

        // Join columns with commas
        for (size_t i = 0; i < columns.size(); ++i) {
            sql << columns[i];
            if (i < columns.size() - 1) sql << ", ";
        }

        sql << " FROM " << fromTable;

        for (const auto& join : joins) {
            sql << join;
        }

        if (!whereClause.empty()) {
            sql << " WHERE " << whereClause << ';';
        }

        return sql.str();
    }
};


class CreateView {
private:
    std::string name;
    std::string selectSql;
    bool replace = false;

public:
    explicit CreateView(std::string_view viewName) : name(viewName) {}

    // Option to replace if exists (DuckDB supports CREATE OR REPLACE VIEW)
    CreateView& OrReplace() {
        replace = true;
        return *this;
    }

    // Accept a built SelectBuilder object
    CreateView& As(const SelectBuilder& builder) {
        selectSql = builder.get();
        return *this;
    }

    // Accept a raw SQL string (in case you have it pre-built)
    CreateView& As(std::string_view sql) {
        selectSql = sql;
        return *this;
    }

    std::string get() const {
        std::ostringstream sql;
        sql << "CREATE ";
        if (replace) sql << "OR REPLACE ";
        sql << "VIEW " << name << " AS " << selectSql;
        return sql.str();
    }
};

// ==========================================
// 3. Utility / DDL Functions
// ==========================================

// Simple function for Drop View
static std::string DropView(std::string_view viewName, bool ifExists = true) {
    std::string sql = "DROP VIEW ";
    if (ifExists) sql += "IF EXISTS ";
    sql += viewName;
    return sql;
}

// Simple function for Add Column
static std::string AddColumn(std::string_view table, std::string_view column, std::string_view type) {
    std::ostringstream sql;
    sql << "ALTER TABLE " << table << " ADD COLUMN " << column << " " << type;
    return sql.str();
}