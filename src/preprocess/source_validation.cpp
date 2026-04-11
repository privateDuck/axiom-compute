#include "source_validation.hpp"
#include "../arrow_fn/read_dataset.hpp"
#include "../arrow_fn/string_df.hpp"
#include <filesystem>
#include <format>
#include <arrow/dataset/api.h>
#include <arrow/filesystem/localfs.h>
#include "../arrow_fn/DuckDBClient.hpp"

namespace preprocess {

    arrow::Status validate_local(const std::string& path, afn::RowWiseStringDF& df) {
        if (!std::filesystem::exists(path)) {
            return arrow::Status::IOError("File does not exist: " + path);
        }
        const auto ext = std::filesystem::path(path).extension().string();
        if (ext != ".csv" && ext != ".parquet" && ext != ".json" && ext != ".ipc") {
            return arrow::Status::IOError("Unsupported file format: " + ext);
        }
        std::shared_ptr<arrow::dataset::FileFormat> format;
        switch (ext[0]) {
            case 'c':
                format = std::make_shared<arrow::dataset::CsvFileFormat>();
                break;
            case 'p':
                format = std::make_shared<arrow::dataset::ParquetFileFormat>();
                break;
            case 'j':
                format = std::make_shared<arrow::dataset::JsonFileFormat>();
                break;
            case 'i':
                format = std::make_shared<arrow::dataset::IpcFileFormat>();
                break;
            default:
                return arrow::Status::IOError("Unsupported file format: " + ext);
        }
        ARROW_ASSIGN_OR_RAISE(const auto fs, arrow::fs::FileSystemFromUriOrPath(path));
        ARROW_ASSIGN_OR_RAISE(const auto reader, afn::ReadLazyFile(fs, format, path));
        std::shared_ptr<arrow::RecordBatch> batch;
        const auto status = reader->ReadNext(&batch);
        if (!status.ok()) {
            return arrow::Status::IOError("Failed to read record batch: " + status.ToString());
        }
        if (batch == nullptr) {
            return arrow::Status::ExecutionError("No record batch found in file: " + path);
        }
        df = afn::RowWiseStringDF(batch);
        return arrow::Status::OK();
    }

    arrow::Status validate_directory(const std::string& base_path, const char file_type, afn::RowWiseStringDF& df) {
        if (!std::filesystem::exists(base_path)) {
            return arrow::Status::IOError("File does not exist: " + base_path);
        }
        std::shared_ptr<arrow::dataset::FileFormat> format;
        switch (file_type) {
            case 'c':
                format = std::make_shared<arrow::dataset::CsvFileFormat>();
                break;
            case 'p':
                format = std::make_shared<arrow::dataset::ParquetFileFormat>();
                break;
            case 'j':
                format = std::make_shared<arrow::dataset::JsonFileFormat>();
                break;
            case 'i':
                format = std::make_shared<arrow::dataset::IpcFileFormat>();
                break;
            default:
                return arrow::Status::IOError(std::format("Unsupported file format: {}", file_type));
        }
        ARROW_ASSIGN_OR_RAISE(const auto fs, arrow::fs::FileSystemFromUriOrPath(base_path));
        const auto localfs = std::make_shared<arrow::fs::LocalFileSystem>();
        ARROW_ASSIGN_OR_RAISE(const auto reader, afn::ScanLazyDirectory(fs, format, base_path));
        std::shared_ptr<arrow::RecordBatch> batch;
        const auto status = reader->ReadNext(&batch);
        if (!status.ok()) {
            return arrow::Status::IOError("Failed to read record batch: " + status.ToString());
        }
        if (batch == nullptr) {
            return arrow::Status::ExecutionError("No record batch found in file: " + base_path);
        }
        df = afn::RowWiseStringDF(batch);
        return arrow::Status::OK();
    }

    arrow::Status validate_file_join(const std::vector<std::string>& file_names, afn::RowWiseStringDF& df) {
        db::DuckDBConnection conn;

        for (const auto& file_name : file_names) {
            const auto path = std::filesystem::path(file_name);
            const std::string query = std::format("CREATE TABLE {} AS SELECT FROM '{}';", path.filename().string(), file_name);
            const auto status = conn.ExecuteQueryNoReturn(query);
            if (!status.ok()) {
                return arrow::Status::IOError("Failed to execute query: " + status.ToString());
            }
        }

        std::shared_ptr<arrow::Table> table;
        const auto result = conn.ExecuteQuery(
            R"(SELECT * EXCLUDE (row_id)
                    FROM (
                        PIVOT (
                            SELECT
                                table_name,
                                column_name || ' (' || data_type || ')' AS col_info,
                                row_number() OVER (PARTITION BY table_name ORDER BY column_index) AS row_id
                            FROM duckdb_columns()
                            WHERE internal = false
                              AND schema_name = 'main'
                        )
                        ON table_name
                        USING FIRST(col_info)
                    )
                    ORDER BY row_id;)",
            table);

        if (!result.ok()) {
            return arrow::Status::ExecutionError("Failed to execute query: " + result.ToString());
        }

        df = afn::RowWiseStringDF(table);
        return arrow::Status::OK();
    }

    arrow::Status validate_db_query(const std::string& connection_str, afn::RowWiseStringDF& df) {
        db::DuckDBConnection conn;
        std::shared_ptr<arrow::Table> table;
        const auto result = conn.ExecuteQuery(
            R"(SELECT * EXCLUDE (row_id)
                    FROM (
                        PIVOT (
                            SELECT
                                table_name,
                                column_name || ' (' || data_type || ')' AS col_info,
                                row_number() OVER (PARTITION BY table_name ORDER BY column_index) AS row_id
                            FROM duckdb_columns()
                            WHERE internal = false
                              AND schema_name = 'main'
                        )
                        ON table_name
                        USING FIRST(col_info)
                    )
                    ORDER BY row_id;)",
            table);

        if (!result.ok()) {
            return arrow::Status::ExecutionError("Failed to execute query: " + result.ToString());
        }

        df = afn::RowWiseStringDF(table);
        return arrow::Status::OK();
    }

    arrow::Status Validate_remote_uri(const std::string& uri, afn::RowWiseStringDF& df) {
        db::DuckDBConnection conn;
        std::shared_ptr<arrow::Table> table;
        const auto status = conn.ExecuteQuery(std::format("SELECT * FROM '{}' LIMIT 25;", uri), table);
        if (!status.ok()) {
            return arrow::Status::IOError("Failed to execute query: " + status.ToString());
        }
        df = afn::RowWiseStringDF(table);
        return arrow::Status::OK();
    }
}