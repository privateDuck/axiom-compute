#pragma once

#include <stdexcept>
#include <duckdb/duckdb.h>
#include <arrow/c/bridge.h>
#include <arrow/api.h>
#include <adbc.h>
#include <format>


namespace db {
    class DuckDBClient {
    public:
        explicit DuckDBClient(const char* path = nullptr) {
            Check(duckdb_open(path, &db_), "Failed to open DB");
            Check(duckdb_connect(db_, &conn_), "Failed to connect");
        }

        [[nodiscard]] std::shared_ptr<arrow::Table> ExecuteQueryInc(const std::string& query) const {

            duckdb_result result;
            if (duckdb_query(conn_, query.c_str(), &result) == DuckDBError) {
                std::string err = duckdb_result_error(&result);
                duckdb_destroy_result(&result);
                throw std::runtime_error("Query Error: " + err);
            }

            idx_t col_count = duckdb_column_count(&result);
            idx_t total_rows = duckdb_row_count(&result);
            idx_t chunk_count = duckdb_result_chunk_count(result);

            for (size_t i = 0; i < col_count; i++) {
                const std::string name = duckdb_column_name(&result, i);
                const auto type = duckdb_column_type(&result, i);

            }
            return nullptr;
        }

        [[nodiscard]] std::shared_ptr<arrow::Table> ExecuteQuery(const std::string& query) const {
            // 1. DuckDB has a dedicated Arrow export mechanism via its C API
            // We execute a query and output it directly to an Arrow stream
            duckdb_arrow arrow_result;
            duckdb_state result_state = duckdb_query_arrow(conn_, query.c_str(), &arrow_result);

            if (result_state == DuckDBError) {
                const std::string err = duckdb_query_arrow_error(arrow_result);
                duckdb_destroy_arrow(&arrow_result);
                throw std::runtime_error("Query Error: " + err);
            }

            // 2. Extract the ArrowSchema C struct
            duckdb_arrow_schema duckdb_schema_ptr {};
            const auto schema_state = duckdb_query_arrow_schema(arrow_result, &duckdb_schema_ptr);
            struct ArrowSchema* c_schema = (struct ArrowSchema*)duckdb_schema_ptr;

            if (schema_state == DuckDBError) {
                duckdb_destroy_arrow(&arrow_result);
                throw std::runtime_error("Schema Extraction Error: ");
            }

            // Convert the C Schema to an Arrow C++ Schema
            const auto schema_result =  arrow::ImportSchema(c_schema);
            if (!schema_result.ok()) {
                const std::string err = schema_result.status().ToString();
                duckdb_destroy_arrow(&arrow_result);
                throw std::runtime_error(err);
            }
            const std::shared_ptr<arrow::Schema>& arrow_schema = schema_result.ValueOrDie();

            std::vector<std::shared_ptr<arrow::RecordBatch>> batches;

            // 3. Iterate through chunks and extract ArrowArray C structs
            while (true) {
                struct ArrowArray c_array;
                duckdb_query_arrow_array(arrow_result, (duckdb_arrow_array*)&c_array);

                // If length is 0 and the release callback is null, the stream is finished
                if (c_array.length == 0 && c_array.release == nullptr) {
                    break;
                }

                // 4. Import the ArrowArray directly into an Arrow RecordBatch
                std::shared_ptr<arrow::RecordBatch> batch =
                    arrow::ImportRecordBatch(&c_array, arrow_schema).ValueOrDie();

                batches.push_back(batch);
            }

            // 5. Combine the chunked RecordBatches into a single Arrow Table
            std::shared_ptr<arrow::Table> final_table =
                arrow::Table::FromRecordBatches(batches).ValueOrDie();

            // Cleanup
            duckdb_destroy_arrow(&arrow_result);

            return final_table;
        }

        ~DuckDBClient() {
            if (db_) { duckdb_close(&db_); }
            if (conn_) { duckdb_disconnect(&conn_); }
        }

    private:

        static void Check(const duckdb_state state, const char* msg) {
            if (state == DuckDBError) throw std::runtime_error(msg);
        }

        duckdb_database db_ = nullptr;
        duckdb_connection conn_ = nullptr;
    };

    class DuckDBConnection {
    public:

        DuckDBConnection() : adbc_database(nullptr), adbc_connection(nullptr) {
            AdbcError adbc_error = ADBC_ERROR_INIT;
            if (AdbcDatabaseNew(&adbc_database, &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to create ADBC database: " + std::string(adbc_error.message));
            }
            if (AdbcDatabaseSetOption(&adbc_database, "driver", R"(duckdb.dll)", &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to set driver option: " + std::string(adbc_error.message));
            }
            if (AdbcDatabaseSetOption(&adbc_database, "entrypoint", "duckdb_adbc_init", &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to set entrypoint option: " + std::string(adbc_error.message));
            }
            if (AdbcDatabaseInit(&adbc_database, &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to initialize ADBC database: " + std::string(adbc_error.message));
            }
            if (AdbcConnectionNew(&adbc_connection, &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to create ADBC Connection: " + std::string(adbc_error.message));
            }
            if (AdbcConnectionInit(&adbc_connection, &adbc_database, &adbc_error) != ADBC_STATUS_OK) {
                throw std::runtime_error("Failed to initialize ADBC connection: " + std::string(adbc_error.message));
            }
        }

        arrow::Status LoadPostgresDriver() {
            return ExecuteQueryNoReturn(R"(LOAD 'postgres_driver.duckdb_extension;')");
        }

        arrow::Status LoadMySQLDriver() {
            return ExecuteQueryNoReturn(R"(LOAD 'mysql_driver.duckdb_extension;')");
        }

        arrow::Status ReadFileAsTable(const std::string& filename, const std::string& table_name) {
            return ExecuteQueryNoReturn(std::format("CREATE TABLE {} AS SELECT * FROM '{}'", table_name, filename));
        }

        arrow::Status ExecuteQuery(const std::string& query, std::shared_ptr<arrow::Table>& table) {
            AdbcError adbc_error = ADBC_ERROR_INIT;
            AdbcStatement adbc_statement;
            ArrowArrayStream arrow_stream;

            if (AdbcStatementNew(&adbc_connection, &adbc_statement, &adbc_error) != ADBC_STATUS_OK) {
                AdbcStatementRelease(&adbc_statement, &adbc_error);
                return arrow::Status::ExecutionError("Failed to create ADBC statement: " + std::string(adbc_error.message));
            }
            if (AdbcStatementSetSqlQuery(&adbc_statement, query.c_str(), &adbc_error) != ADBC_STATUS_OK) {
                AdbcStatementRelease(&adbc_statement, &adbc_error);
                return arrow::Status::ExecutionError("Failed to set SQL query: " + std::string(adbc_error.message));
            }
            int64_t rows_affected;
            if(AdbcStatementExecuteQuery(&adbc_statement, &arrow_stream, &rows_affected, &adbc_error) != ADBC_STATUS_OK) {
                AdbcStatementRelease(&adbc_statement, &adbc_error);
                return arrow::Status::ExecutionError("Failed to execute query: " + std::string(adbc_error.message));
            }
            AdbcStatementRelease(&adbc_statement, &adbc_error);

            ARROW_ASSIGN_OR_RAISE(const auto reader, arrow::ImportRecordBatchReader(&arrow_stream));
            ARROW_ASSIGN_OR_RAISE(table, reader->ToTable());
            // arrow_stream.release(&arrow_stream);
            return arrow::Status::OK();
        }

        arrow::Status ExecuteQueryNoReturn(const std::string& query) {
            AdbcError adbc_error = ADBC_ERROR_INIT;
            AdbcStatement adbc_statement;
            ArrowArrayStream arrow_stream;

            auto status = AdbcStatementNew(&adbc_connection, &adbc_statement, &adbc_error);
            if (status != ADBC_STATUS_OK) {
                return arrow::Status::ExecutionError("Failed to create ADBC statement: " + std::string(adbc_error.message));
            }
            status = AdbcStatementSetSqlQuery(&adbc_statement, query.c_str(), &adbc_error);
            if (status != ADBC_STATUS_OK) {
                return arrow::Status::ExecutionError("Failed to set SQL query: " + std::string(adbc_error.message));
            }
            int64_t rows_affected;
            status = AdbcStatementExecuteQuery(&adbc_statement, &arrow_stream, &rows_affected, &adbc_error);
            if(status != ADBC_STATUS_OK) {
                return arrow::Status::ExecutionError("Failed to execute query: " + std::string(adbc_error.message));
            }

            arrow_stream.release(&arrow_stream);
            AdbcStatementRelease(&adbc_statement, &adbc_error);
            return arrow::Status::OK();
        }

        ~DuckDBConnection() {
            AdbcError adbc_error = ADBC_ERROR_INIT;
            AdbcConnectionRelease(&adbc_connection, &adbc_error);
            AdbcDatabaseRelease(&adbc_database, &adbc_error);
        }

    private:
        AdbcDatabase adbc_database;
        AdbcConnection adbc_connection;
    };
}
