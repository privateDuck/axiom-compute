#pragma once

#include <arrow/api.h>
#include <arrow/compute/api.h>
#include "infer_types.hpp"
#include "read_file.hpp"

namespace preprocess {

    class PreprocessorContext {
    public:
        PreprocessorContext();
        static void Validate(SourceType src, const std::vector<std::string>& args);
    private:
        std::shared_ptr<arrow::Table> table;
    };

    inline PreprocessorContext::PreprocessorContext() {
    }

}
