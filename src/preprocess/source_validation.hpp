#pragma once

#include <arrow/api.h>
#include "../arrow_fn/string_df.hpp"

namespace preprocess {

    enum class SourceType {
        LocalFile,
        DatasetDirectory,
        CombineFiles,
        RemoteURI,
        DatabaseConnection,
    };

    arrow::Status validate_local(const std::string& path, afn::RowWiseStringDF& df);
    arrow::Status validate_directory(const std::string& base_path, const char file_type, afn::RowWiseStringDF& df);
    arrow::Status validate_file_join(const std::vector<std::string>& file_names, afn::RowWiseStringDF& df);
    arrow::Status validate_db_query(const std::string& connection_str, afn::RowWiseStringDF& df);
    arrow::Status Validate_remote_uri(const std::string& uri, afn::RowWiseStringDF& df);

    bool Validate(SourceType src, const std::vector<std::string>& args);

}
