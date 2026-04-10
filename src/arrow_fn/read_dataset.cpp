
#include <iostream>
#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/compute/cast.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/ipc/writer.h>
#include <arrow/util/iterator.h>


namespace ds = arrow::dataset;
namespace fs = arrow::fs;
namespace cp = arrow::compute;

namespace afn {

    arrow::Result<std::shared_ptr<arrow::Table>> ScanEagerDirectory(
        const std::shared_ptr<fs::FileSystem>& filesystem,
        const std::shared_ptr<ds::FileFormat>& format, const std::string& base_dir, const int64_t batch_size) {

        fs::FileSelector selector;
        selector.base_dir = base_dir;
        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(filesystem, selector, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        // Read the entire dataset as a Table
        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_RETURN_NOT_OK(scan_builder->BatchSize(batch_size));
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToTable();
    }

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ScanLazyDirectory(
        const std::shared_ptr<fs::FileSystem>& filesystem,
        const std::shared_ptr<ds::FileFormat>& format, const std::string& base_dir) {

        fs::FileSelector selector;
        selector.base_dir = base_dir;
        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(filesystem, selector, format, options));

        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToRecordBatchReader();
    }

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFile(
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

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFileURI(
        const std::shared_ptr<ds::FileFormat> &format,
        const std::string &uri) {

        const auto options = ds::FileSystemFactoryOptions();
        ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(uri, format, options));
        ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

        ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
        return scanner->ToRecordBatchReader();
    }

    arrow::Status ReadCloudDataset(const std::string& uri) {
        // 1. Automatically resolve the Filesystem (S3, GCS, Azure) from the URI
        std::string path;
        std::shared_ptr<arrow::fs::FileSystem> fs;

        // ARROW_ASSIGN_OR_RAISE unpacks the Result or returns the Status on error
        ARROW_ASSIGN_OR_RAISE(fs, arrow::fs::FileSystemFromUri(uri, &path));

        // 2. Specify the file format (assuming Parquet here)
        auto format = std::make_shared<arrow::dataset::ParquetFileFormat>();

        // 3. Create the Dataset Factory
        arrow::dataset::FileSystemFactoryOptions options;
        ARROW_ASSIGN_OR_RAISE(auto factory,
            arrow::dataset::FileSystemDatasetFactory::Make(fs, {path}, format, options));

        // 4. Finish the dataset creation
        ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());

        // 5. Scan the dataset into memory (Arrow Table)
        ARROW_ASSIGN_OR_RAISE(auto scanner_builder, dataset->NewScan());
        ARROW_ASSIGN_OR_RAISE(auto scanner, scanner_builder->Finish());
        ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());

        std::cout << "Successfully read " << table->num_rows() << " rows from " << uri << std::endl;
        return arrow::Status::OK();
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

    void fn() {
        std::shared_ptr<arrow::RecordBatch> batch;

        while (true) {
            // ReadNext populates 'batch' and returns an arrow::Status
            arrow::Status status = reader->ReadNext(&batch);

            if (!status.ok()) {
                std::cerr << "Error reading batch: " << status.ToString() << std::endl;
                break;
            }

            // A nullptr means we have reached the end of the data stream
            if (batch == nullptr) {
                break;
            }

            std::cout << "Read a batch with " << batch->num_rows() << " rows." << std::endl;

            const auto arr = batch->column(0);
        }
    }

}