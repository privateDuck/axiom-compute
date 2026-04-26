#pragma once

#include <arrow/api.h>
#include <arrow/dataset/dataset.h>
#include <arrow/filesystem/filesystem.h>

namespace afn {
    arrow::Result<std::shared_ptr<arrow::Table>> ScanEagerDirectory(
        const std::shared_ptr<arrow::fs::FileSystem> &filesystem,
        const std::shared_ptr<arrow::dataset::FileFormat> &format, const std::string &base_dir
    );

    arrow::Result<std::shared_ptr<arrow::Table>> ScanEagerDirectory(
        const std::string& extension, const std::string &base_dir
    );


    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ScanLazyDirectory(
        const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
        const std::shared_ptr<arrow::dataset::FileFormat>& format,
        const std::string& base_dir, int64_t batch_size = -1
    );

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFile(
        const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
        const std::shared_ptr<arrow::dataset::FileFormat>& format,
        const std::string& file_path, int64_t batch_size = -1
    );

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFile(const std::string& path);
    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFile(const std::string& path, int64_t batch_size = -1);

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFileURI(const std::string& uri);

    arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFileURI(
        const std::shared_ptr<arrow::dataset::FileFormat>& format,
        const std::string& uri
    );

    arrow::Result<std::shared_ptr<arrow::RecordBatchReader>> ReadLazyFileURI(
        const std::shared_ptr<arrow::dataset::FileFormat> &format,
        const std::string &uri, int64_t batch_size = -1
    );

    arrow::Result<std::shared_ptr<arrow::Table>> ReadDatabaseConnection(
        const std::string& connection_string, const std::string& query
    );

    arrow::Result<std::shared_ptr<arrow::Table>> ReadJoinedFileSet(
        const std::vector<std::string>& files, const std::string& query
    );
}