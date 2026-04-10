#pragma once

#include <arrow/api.h>
#include "types.hpp"

namespace preprocess {

    enum class SourceType {
        LocalFile,
        DatasetDirectory,
        CombineFiles,
        RemoteURI,
        DatabaseConnection,
    };

    bool Validate(SourceType src, const std::vector<std::string>& args);

}
