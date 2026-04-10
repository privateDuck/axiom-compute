#pragma once

#include <atomic>
#include <memory>
#include "interop_types.h"
#include "interop_builder.hpp"

namespace top {
    enum TaskStatus : int32_t {
        Error = -1,
        Running = 0,
        Success = 1,
    };

    struct AsyncTask {
        CResult* result {nullptr};
        std::unique_ptr<ResultBuilder> builder;
        int32_t id;
        std::atomic<TaskStatus> status {Running};

        AsyncTask() = default;
        ~AsyncTask() {
            delete result;
        }

        AsyncTask(const AsyncTask&) = delete;
        AsyncTask& operator=(const AsyncTask&) = delete;
    };
}