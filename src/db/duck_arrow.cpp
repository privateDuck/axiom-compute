#include <duckdb/duckdb.h>
#include <arrow/api.h>
#include <arrow/c/bridge.h>
#include <adbc.h>


void adbc_duck() {
    AdbcError adbc_error;
    AdbcDatabase adbc_database;
    AdbcConnection adbc_connection;
    AdbcStatement adbc_statement;
    ArrowArrayStream arrow_stream;

    AdbcDatabaseNew(&adbc_database, &adbc_error);
    AdbcDatabaseSetOption(&adbc_database, "driver", R"(E:\axiom\atlas\lib\duckdb.lib)", &adbc_error);
    AdbcDatabaseSetOption(&adbc_database, "entrypoint", "duckdb_adbc_init", &adbc_error);
    AdbcDatabaseInit(&adbc_database, &adbc_error);
    AdbcConnectionNew(&adbc_connection, &adbc_error);
    AdbcConnectionInit(&adbc_connection, &adbc_database, &adbc_error);

    AdbcStatementNew(&adbc_connection, &adbc_statement, &adbc_error);
    AdbcStatementSetSqlQuery(&adbc_statement, "SELECT 42", &adbc_error);
    int64_t rows_affected;
    AdbcStatementExecuteQuery(&adbc_statement, &arrow_stream, &rows_affected, &adbc_error);
    arrow_stream.release(&arrow_stream);
}


void bulk_append_int32(const idx_t col_idx, duckdb_result* res, arrow::Int32Builder& id_builder) {

    duckdb_arrow arrow_result;
    duckdb_query_arrow(con, "SELECT id::INT, name::VARCHAR FROM my_table", &arrow_result);
    struct ArrowSchema c_schema;
    duckdb_query_arrow_schema(arrow_result, reinterpret_cast<duckdb_arrow_schema *>(&c_schema));

    while (true) {
        duckdb_data_chunk result = duckdb_fetch_chunk(*res);
        if (!result) {
            break;
        }
        const auto chunk_size = duckdb_data_chunk_get_size(result);

        idx_t row_count = duckdb_data_chunk_get_size(result);
        duckdb_vector res_col = duckdb_data_chunk_get_vector(result, col_idx);
        auto type = duckdb_column_type(res, col_idx);

        const int32_t* raw_data = static_cast<int32_t*>(duckdb_vector_get_data(res_col));
        const uint64_t* validity_mask = static_cast<uint64_t*>(duckdb_vector_get_validity(res_col));
        const auto arrow_valid_bytes = reinterpret_cast<const uint8_t*>(validity_mask);

        arrow::Status status = id_builder.AppendValues(raw_data, chunk_size, arrow_valid_bytes);
        if (!status.ok()) {
            throw std::runtime_error("Append failed: " + status.ToString());
        }

        duckdb_destroy_data_chunk(&result);
    }
}