#include "source_validation.hpp"
#include "read_file.hpp"
#include <filesystem>
#include <arrow/dataset/api.h>

namespace preprocess {

    ValidationResult validate_local(const std::vector<std::string>& file_paths) {
        if (file_paths.empty()) {
            return ValidationResult(false);
        }
        for (const auto& path : file_paths) {
            if (!std::filesystem::exists(path)) {
                return false;
            }
            const auto ext = std::filesystem::path(path).extension().string();
            if (ext != ".csv" && ext != ".parquet" && ext != ".json" && ext != ".ipc") {
                return false;
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
                    return false;
            }
            const auto fs = arrow::fs::FileSystemFromUri(path);
            if (fs.ok()) {
                const auto result = ReadEagerFile(fs.ValueOrDie(), format, path, 10);
                if ( result.ok() ) {
                    const auto sptr = result.ValueOrDie();
                    // stringstream -> push first n rows
                    for (const auto col : sptr->columns()) {

                    }
                }
            }
        }
        return true;
    }

    bool Validate(SourceType src, const std::vector<std::string> &args) {

    }
}