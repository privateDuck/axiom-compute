#pragma once

#include <duckdb/duckdb.h>
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <concepts>
#include <span>
#include <cstring>
#include <Eigen/Eigen>
#include <unordered_map>
#include <format>
#include "DuckBinder.hpp"
#include "DataFrame.hpp"


class DuckDBClient {
    duckdb_database db_ = nullptr;
    duckdb_connection conn_ = nullptr;
    //std::unordered_map<std::string, std::shared_ptr<DataFrame>> active_tables;

    void Check(duckdb_state state, const char* msg) {
        if (state == DuckDBError) throw std::runtime_error(msg);
    }

public:
    DuckDBClient(const char* path = nullptr) {
        Check(duckdb_open(path, &db_), "Failed to open DB");
        Check(duckdb_connect(db_, &conn_), "Failed to connect");
    }

    ~DuckDBClient() {
        if (conn_) duckdb_disconnect(&conn_);
        if (db_) duckdb_close(&db_);
    }

    duckdb_connection GetConn() {
        return conn_;
    }

	// Executes the query and returns the result as a DataFrame of contiguous columnar data
    // Involves copying memory
    std::shared_ptr<DataFrame> ReturnQuery(const std::string& sql) {
        duckdb_result result;
        if (duckdb_query(conn_, sql.c_str(), &result) == DuckDBError) {
            std::string err = duckdb_result_error(&result);
            duckdb_destroy_result(&result);
            throw std::runtime_error("Query Error: " + err);
        }

        std::shared_ptr<DataFrame> table = std::make_shared<DataFrame>();
        idx_t col_count = duckdb_column_count(&result);
        idx_t total_rows = duckdb_row_count(&result);
        idx_t chunk_count = duckdb_result_chunk_count(result);

        // 1. Initialize Columns
        for (idx_t i = 0; i < col_count; i++) {
            std::string name = duckdb_column_name(&result, i);
            auto type = duckdb_column_type(&result, i);
            auto internal_type = IColumn::FromDuckType(type);

            std::shared_ptr<IColumn> col;

            // Allocate and Reserve Memory upfront
            if (internal_type == ColType::INT64) {
                col = std::make_shared<Column<int64_t>>(ColType::INT64);
                col->Reserve(total_rows);
            }
            else if (internal_type == ColType::FLOAT) {
                col = std::make_shared<Column<float>>(ColType::FLOAT);
                col->Reserve(total_rows);
            }
            else if (internal_type == ColType::VARCHAR) {
                col = std::make_shared<Column<std::string>>(ColType::VARCHAR);
                col->Reserve(total_rows);
            }
            else {
                // Fallback or skip
                duckdb_destroy_result(&result);
                throw std::runtime_error("Unsupported column type in query result");
            }
            table->AddColumn(name, col);
        }

        // 2. Fetch Data Chunk by Chunk (Fast Path)
        for (idx_t c = 0; c < chunk_count; c++) {
            duckdb_data_chunk chunk = duckdb_result_get_chunk(result, c);
            idx_t rows_in_chunk = duckdb_data_chunk_get_size(chunk);

            for (idx_t col_idx = 0; col_idx < col_count; col_idx++) {
                duckdb_vector vec = duckdb_data_chunk_get_vector(chunk, col_idx);
                auto& col_ptr = table->GetColumn(col_idx);

                // Get raw C pointer from DuckDB
                void* raw_data = duckdb_vector_get_data(vec);

                // COPY logic based on type
                if (col_ptr->GetType() == ColType::INT64) {
                    auto* typed_col = static_cast<Column<int64_t>*>(col_ptr.get());
                    typed_col->AppendBlock(static_cast<int64_t*>(raw_data), rows_in_chunk);
                }
                else if (col_ptr->GetType() == ColType::FLOAT) {
                    auto* typed_col = static_cast<Column<float>*>(col_ptr.get());
                    typed_col->AppendBlock(static_cast<float*>(raw_data), rows_in_chunk);
                }
                else if (col_ptr->GetType() == ColType::VARCHAR) {
                    // String handling is special: DuckDB returns duckdb_string_t
                    auto* typed_col = static_cast<Column<std::string>*>(col_ptr.get());
                    duckdb_string_t* str_data = static_cast<duckdb_string_t*>(raw_data);

                    for (idx_t r = 0; r < rows_in_chunk; ++r) {
                        // Check inline vs pointer string in DuckDB
                        if (duckdb_string_is_inlined(str_data[r])) {
                            typed_col->Append(std::string(str_data[r].value.inlined.inlined, str_data[r].value.inlined.length));
                        }
                        else {
                            typed_col->Append(std::string(str_data[r].value.pointer.ptr, str_data[r].value.pointer.length));
                        }
                    }
                }
            }
            duckdb_destroy_data_chunk(&chunk);
        }

        /*duckdb_statement_type res_stmt_type = duckdb_result_statement_type(result);
        duckdb_destroy_result(&result);

        if (res_stmt_type == DUCKDB_STATEMENT_TYPE_SELECT) {
            size_t idx_from = sql.find("FROM");
            
        }*/
        return table;
    }

    void QueryNoReturn(const std::string& sql) {
        duckdb_result result;
        if (duckdb_query(conn_, sql.c_str(), &result) == DuckDBError) {
            std::string err = duckdb_result_error(&result);
            duckdb_destroy_result(&result);
            throw std::runtime_error("Query Error: " + err);
        }
    }

    // Writer using appender. 
    // Row Wise - Faster for a small number of rows
    void WriteToDB(const std::string& table_name, const DataFrame& table) {
        if (table.ColCount() == 0) return;

        // 1. Generate CREATE TABLE Statement
        std::string create_sql = "CREATE OR REPLACE TABLE " + table_name + " (";
        for (size_t i = 0; i < table.ColCount(); ++i) {
            create_sql += table.GetName(i) + " ";
            switch (table.GetColumn(i)->GetType()) {
            case ColType::INT64: create_sql += "BIGINT"; break;
            case ColType::FLOAT: create_sql += "FLOAT"; break;
            case ColType::VARCHAR: create_sql += "VARCHAR"; break;
            default: throw std::runtime_error("Unknown type for create");
            }
            if (i < table.ColCount() - 1) create_sql += ", ";
        }
        create_sql += ");";

        // Execute CREATE
        if (duckdb_query(conn_, create_sql.c_str(), nullptr) == DuckDBError) {
            throw std::runtime_error("Failed to create table");
        }

        // 2. Initialize Appender
        duckdb_appender appender;
        if (duckdb_appender_create(conn_, nullptr, table_name.c_str(), &appender) == DuckDBError) {
            throw std::runtime_error("Failed to create appender");
        }

        // 3. Append Data (Row by Row)
        // DuckDB C Appender is fastest when iterating rows
        size_t row_count = table.RowCount();
        size_t col_count = table.ColCount();

        for (size_t r = 0; r < row_count; ++r) {
            duckdb_appender_begin_row(appender);

            for (size_t c = 0; c < col_count; ++c) {
                auto& col = table.GetColumn(c);

                if (col->GetType() == ColType::INT64) {
                    auto* typed = static_cast<Column<int64_t>*>(col.get());
                    duckdb_append_int64(appender, typed->GetData()[r]);
                }
                else if (col->GetType() == ColType::FLOAT) {
                    auto* typed = static_cast<Column<float>*>(col.get());
                    duckdb_append_float(appender, typed->GetData()[r]);
                }
                else if (col->GetType() == ColType::VARCHAR) {
                    auto* typed = static_cast<Column<std::string>*>(col.get());
                    const std::string& str = typed->GetData()[r];
                    duckdb_append_varchar_length(appender, str.c_str(), str.length());
                }
            }

            duckdb_appender_end_row(appender);
        }

        duckdb_appender_flush(appender);
        duckdb_appender_close(appender);
        duckdb_appender_destroy(&appender);
    }

    // Writes the contents of the DataFrame object to a DuckDB table with the given name
    // Zero Copy (Kind of) - The DuckDB DataFrame would reference the table directly.
    // DataFrame object must stay in memory!!
    void WriteToDBAsReference(const std::string& table_name, const DataFrame& table) {
        RegisterScanFunction(conn_, "scan_memory");
        DataFrame* tbl_ptr = const_cast<DataFrame*>(&table);
        int64_t ptr_val = reinterpret_cast<int64_t>(tbl_ptr);

        std::string sql = std::format("CREATE VIEW {} AS SELECT * FROM scan_memory({});", table_name, ptr_val);

        QueryNoReturn(sql);
    }

    // Copies the contents of the DataFrame object to a DuckDB table with the given name
    void WriteToDBPersistent(const std::string& table_name, const DataFrame& table) {
        RegisterScanFunction(conn_, "scan_memory");
        DataFrame* tbl_ptr = const_cast<DataFrame*>(&table);
        int64_t ptr_val = reinterpret_cast<int64_t>(tbl_ptr);

        std::string sql = std::format("CREATE TABLE {} AS SELECT * FROM scan_memory({});", table_name, ptr_val);

        QueryNoReturn(sql);
    }
};