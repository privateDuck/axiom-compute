#pragma once

#include <types.hpp>

namespace preprocess {

    struct TryParseInfo {
        float success_rate;
        float fail_rate;
    };

    struct TypeInfo {
        Type inferred_type;
        Type fallback_type;
        float confidence;
        float error_rate;
    };

}