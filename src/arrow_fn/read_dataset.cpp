
#include <filesystem>
#include <iostream>
#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_csv.h>
#include <arrow/dataset/file_ipc.h>
#include <arrow/dataset/file_json.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/filesystem/localfs.h>
#include <arrow/ipc/writer.h>
#include <arrow/util/iterator.h>
#include <re2/re2.h>
#include "DuckDBClient.hpp"

namespace ds = arrow::dataset;
namespace fs = arrow::fs;
namespace cp = arrow::compute;

namespace afn {

    arrow::Result<std::shared_ptr<arrow::Table>> ScanEagerDirectory(
        const std::shared_ptr<fs::FileSystem> &filesystem,
        const std::shared_ptr<ds::FileFormat> &format, const std::string &base_dir) {

        fs::FileSelector selector;
        selector.base_dir = base_dir;
        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(filesystem, selector, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        // Read the entire dataset as a Table
        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToTable();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ScanEagerDirectory(const std::string& extension, const std::string &base_dir) {
        switch (extension[0]) {
            case 'c':
                return ScanEagerDirectory(std::make_shared<fs::LocalFileSystem>(), std::make_shared<ds::CsvFileFormat>(), base_dir);
            case 'p':
                return ScanEagerDirectory(std::make_shared<fs::LocalFileSystem>(), std::make_shared<ds::ParquetFileFormat>(), base_dir);
            case 'j':
                return ScanEagerDirectory(std::make_shared<fs::LocalFileSystem>(), std::make_shared<ds::JsonFileFormat>(), base_dir);
            case 'i':
                return ScanEagerDirectory(std::make_shared<fs::LocalFileSystem>(), std::make_shared<ds::IpcFileFormat>(), base_dir);
            default:
                return arrow::Status::ExecutionError("Unsupported file format: " + extension);
        }
    }

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ScanLazyDirectory(
            const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
            const std::shared_ptr<arrow::dataset::FileFormat>& format,
            const std::string& base_dir, int64_t batch_size = -1
        ) {

        fs::FileSelector selector;
        selector.base_dir = base_dir;
        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(filesystem, selector, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        if (batch_size != -1)
            ARROW_RETURN_NOT_OK(scan_builder->BatchSize(batch_size));
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToRecordBatchReader();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFile(
        const std::shared_ptr<fs::FileSystem> &filesystem,
        const std::shared_ptr<ds::FileFormat> &format,
        const std::string &file_path) {
        const auto options = ds::FileSystemFactoryOptions();

        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(
            filesystem, {file_path}, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());
        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());

        return scanner->ToTable();
    }

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFile(
        const std::shared_ptr<fs::FileSystem>& filesystem,
        const std::shared_ptr<ds::FileFormat>& format,
        const std::string& file_path, const int64_t batch_size) {
        const auto options = ds::FileSystemFactoryOptions();

        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(
            filesystem, {file_path}, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());
        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        if (batch_size != -1)
            ARROW_RETURN_NOT_OK(scan_builder->BatchSize(batch_size));
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());

        return scanner->ToRecordBatchReader();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFile(const std::string& path) {
        const std::filesystem::path path_obj(path);
        const char ext = path_obj.extension().string()[1];
        std::shared_ptr<arrow::dataset::FileFormat> format;
        bool isExcel = false;
        switch (ext) {
            case 'p': // Parquet
                format = std::make_shared<arrow::dataset::ParquetFileFormat>();
                break;
            case 'c': // csv
                format = std::make_shared<arrow::dataset::CsvFileFormat>();
                break;
            case 'j': // json
                format = std::make_shared<arrow::dataset::JsonFileFormat>();
                break;
            case 'i': // ipc
                format = std::make_shared<arrow::dataset::IpcFileFormat>();
                break;
            case 'x': // xlsx
                isExcel = true;
                break;
            default:
                return arrow::Status::ExecutionError("Invalid File Extension");
        }
        if (!isExcel) {
            ARROW_ASSIGN_OR_RAISE(const auto fs, arrow::fs::FileSystemFromUriOrPath(path));
            return ReadEagerFile(fs, format, path);
        }

        db::DuckDBConnection conn;
        std::shared_ptr<arrow::Table> table;
        RETURN_NOT_OK(conn.ExecuteQuery(std::format("SELECT * FROM '{}';", path), table));
        return table;
    }

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFile(const std::string& path, const int64_t batch_size) {
        const std::filesystem::path path_obj(path);
        const char ext = path_obj.extension().string()[1];
        std::shared_ptr<arrow::dataset::FileFormat> format;
        switch (ext) {
            case 'p': // Parquet
                format = std::make_shared<arrow::dataset::ParquetFileFormat>();
                break;
            case 'c': // csv
                format = std::make_shared<arrow::dataset::CsvFileFormat>();
                break;
            case 'j': // json
                format = std::make_shared<arrow::dataset::JsonFileFormat>();
                break;
            case 'i': // ipc
                format = std::make_shared<arrow::dataset::IpcFileFormat>();
                break;
            case 'x': // xlsx
            default:
                return arrow::Status::ExecutionError("Cannot read excel files as a record batch");
        }
        ARROW_ASSIGN_OR_RAISE(const auto fs, arrow::fs::FileSystemFromUriOrPath(path));
        return ReadLazyFile(fs, format, path, batch_size);
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFileURI(
        const std::shared_ptr<ds::FileFormat>& format,
        const std::string& uri) {

        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(uri, format, options));
        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToTable();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFileURI(const std::string& uri) {
        db::DuckDBConnection conn;
        std::shared_ptr<arrow::Table> table;
        RETURN_NOT_OK(conn.ExecuteQuery(std::format("SELECT * FROM '{}';", uri), table));
        return table;
    }

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFileURI(
        const std::shared_ptr<ds::FileFormat> &format,
        const std::string &uri, const int64_t batch_size ) {

        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(uri, format, options));
        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        if (batch_size != -1)
            ARROW_RETURN_NOT_OK(scan_builder->BatchSize(batch_size));
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToRecordBatchReader();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadDatabaseConnection(
        const std::string& connection_string, const std::string& query
    ) {
        // 1. We have to first parse the query to extract the
        // let's assume the connection string is in the format: "driver://user:password@host:port/database?parameters"
        const RE2 pattern(R"(^(\w+)://(?:([^:]+)(?::([^@]+))?@)?([^:/]+)(?::(\d+))?/([^?]+)(?:\?(.*))?$)");
        re2::StringPiece driver, user, password, host, port, database, params;
        if (RE2::FullMatch(connection_string, pattern, &driver, &user, &password, &host, &port, &database, &params)) {
            db::DuckDBConnection conn;
            if (driver == "postgres") {
                RETURN_NOT_OK(conn.LoadPostgresDriver());
            }
            else {
                RETURN_NOT_OK(conn.LoadMySQLDriver());
            }
            RETURN_NOT_OK(conn.ExecuteQueryNoReturn(std::format("ATTACH '{}' (TYPE {}, READ_ONLY);", connection_string, driver)));
            RETURN_NOT_OK(conn.ExecuteQueryNoReturn(std::format("USE {};", database)));

            std::shared_ptr<arrow::Table> table;
            RETURN_NOT_OK(conn.ExecuteQuery(query, table));

            return table;
        }
        return arrow::Status::ExecutionError("Invalid connection string format");
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadJoinedFileSet(
        const std::vector<std::string>& files, const std::string& query
    ) {
        db::DuckDBConnection conn;
        for (const auto& filename : files) {
            RETURN_NOT_OK(conn.ReadFileAsTable(filename, std::filesystem::path(filename).stem().string()));
        }
        std::shared_ptr<arrow::Table> table;
        RETURN_NOT_OK(conn.ExecuteQuery(query, table));
        return table;
    }
    /*
    #include <arrow/filesystem/s3fs.h>
    #include <arrow/filesystem/azurefs.h>
    #include <arrow/filesystem/gcsfs.h>

    arrow::Result<std::shared_ptr<arrow::fs::FileSystem>> CreateS3FileSystem(
        const std::string& access_key,
        const std::string& secret_key,
        const std::string& region)
    {
        // Pass the explicit keys. You can also pass a session token as a third argument if needed.
        arrow::fs::S3Options options = arrow::fs::S3Options::FromAccessKey(access_key, secret_key);
        options.region = region;

        // Create the file system
        return arrow::fs::S3FileSystem::Make(options);
    }

    arrow::Result<std::shared_ptr<arrow::fs::FileSystem>> CreateGcsFileSystem(
        const std::string& json_credentials)
    {
        // Pass the raw JSON string of the GCP Service Account
        arrow::fs::GcsOptions options =
            arrow::fs::GcsOptions::FromServiceAccountCredentials(json_credentials);
        //arrow::fs::GcsOptions::FromAccessToken(token)
        // Create the file system
        return fs::GcsFileSystem::Make(options);
    }

    arrow::Result<std::shared_ptr<fs::FileSystem>> CreateAzureFileSystem(
        const std::string& account_name,
        const std::string& account_key)
    {
        fs::AzureOptions options; // Starts with defaults

        // Inject the credentials
        arrow::Status st = options.ConfigureAccountKeyCredential(account_key);
        options.account_name = account_name;
        if (!st.ok()) return st; // Return the error if configuration fails

        // Create the file system
        return fs::AzureFileSystem::Make(options);
    }
    */
}