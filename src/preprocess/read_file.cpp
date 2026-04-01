
#include <iostream>
#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/compute/cast.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_ipc.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/ipc/writer.h>
#include <arrow/util/iterator.h>
#include "arrow/compute/expression.h"


namespace ds = arrow::dataset;
namespace fs = arrow::fs;
namespace cp = arrow::compute;

void ReadFile(const std::string& filename) {
    const arrow::io::IOContext& io_context = arrow::io::default_io_context();
    auto input_res = arrow::io::ReadableFile::Open(filename);
    if (!input_res.ok()) {
        throw std::runtime_error("Failed to Open File");
    }
    std::shared_ptr<arrow::io::InputStream> input = *input_res;

    auto read_opt = arrow::csv::ReadOptions::Defaults();
    auto parse_options = arrow::csv::ParseOptions::Defaults();
    auto convert_options = arrow::csv::ConvertOptions::Defaults();

    read_opt.autogenerate_column_names = true;
    read_opt.use_threads = true;

    auto maybe_reader = arrow::csv::TableReader::Make(
        io_context,
        input,
        read_opt,
        parse_options,
        convert_options
    );

    if (!maybe_reader.ok()) {
        throw std::runtime_error("Failed to read file");
    }
    const std::shared_ptr<arrow::csv::TableReader>& reader = *maybe_reader;

    auto table_res = reader->Read();
    if (!table_res.ok()) {
        throw std::runtime_error("Failed to read table: " + table_res.status().ToString());
    }
    auto single_chunk_res = (*table_res)->CombineChunks();

    if (!single_chunk_res.ok()) {
        throw std::runtime_error("Failed to combine chunks: " + table_res.status().ToString());
    }

    return *single_chunk_res;
}

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

arrow::Result<std::shared_ptr<arrow::Table>> ReadEagerFile(
    const std::shared_ptr<fs::FileSystem>& filesystem,
    const std::shared_ptr<ds::FileFormat>& format,
    const std::string& file_path, const int64_t batch_size) {
    ARROW_ASSIGN_OR_RAISE(const auto uri, filesystem->MakeUri(file_path));
    const auto options = ds::FileSystemFactoryOptions();
    ARROW_ASSIGN_OR_RAISE(const auto factory, ds::FileSystemDatasetFactory::Make(uri, format, options));
    ARROW_ASSIGN_OR_RAISE(const auto dataset, factory->Finish());

    ARROW_ASSIGN_OR_RAISE(const auto scan_builder, dataset->NewScan());
    ARROW_RETURN_NOT_OK(scan_builder->BatchSize(batch_size));
    ARROW_ASSIGN_OR_RAISE(const auto scanner, scan_builder->Finish());
    return scanner->ToTable();
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