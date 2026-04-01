#pragma once
#include <unordered_map>
#include <queue>
#include <atomic>
#include <../include/spdlog/spdlog.h>
#include "../preprocess/preprocessor_ctx.hpp"

namespace top {

    enum TaskStatus : int32_t {
        Error = -1,
        Running = 0,
        Success = 1,
    };

    struct alignas(16) TaskHandle {
        uint64_t ptr;
        int32_t id;
        std::atomic<TaskStatus> status;

        TaskHandle& operator=(const TaskHandle& rhs) {
            ptr = rhs.ptr;
            id = rhs.id;
            return *this;
        }
        TaskHandle(const TaskHandle& rhs) : ptr(rhs.ptr), id(rhs.id), status(rhs.status.load()) {}
        TaskHandle(const uint64_t ptr, const int32_t id, const TaskStatus status) : ptr(ptr), id(id), status(status) {}
        TaskHandle() : ptr(0), id(0), status(Error) {}
    };

    class GlobalContextHandle {
    public:
        GlobalContextHandle() : ppctx(nullptr) {
            task_free_list.reserve(4096);
            tasks.reserve(4096);
            for (int32_t i = 0; i < 4096; ++i) {
                task_free_list[i] = 4095 - i;
            }
        }

        template<typename... Args>
        void LogInfo(spdlog::format_string_t<Args...> fmt, Args &&...args) {
            spdlog::info(fmt, std::forward<Args>(args)...);
        }
        template<typename... Args>
        void LogWarn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
            spdlog::info(fmt, std::forward<Args>(args)...);
        }
        template<typename... Args>
        void LogCritical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
            spdlog::info(fmt, std::forward<Args>(args)...);
        }

        void ExitSafe(int code) const {
            spdlog::info("Exiting with code {}", code);
            // Release all resources here
            if (ppctx) delete ppctx;
        }

        static void* AllocateResult(const size_t bytes) {
            return malloc(bytes);
        }

        template<typename T>
        static void* AllocateResult(const T&) {
            return malloc(sizeof(T));
        }

        void SetTaskStatus(const int32_t id, const TaskStatus status) const {
            tasks.at(id)->status = status;
        }

        void FreeTaskHandle(const int32_t id) {
            if (id < tasks.size()) {
                const auto* task = tasks.at(id);
                if (task->status == Running) {
                    spdlog::warn("Freeing a task handle that is still running: {}", id);
                }
                if (task->ptr != 0)
                    free(reinterpret_cast<void*>(task->ptr));
                task_free_list.push_back(id);
                delete task;
            }
        }

        TaskHandle* PushTask(const uint64_t ptr) {
            const auto id = task_free_list.back();
            task_free_list.pop_back();
            const auto handle = new TaskHandle{ptr, id, Running};
            tasks[id] = handle;
            return handle;
        }

        void CreatePreprocessorContext(const SourceType src, const std::vector<std::string>& args) {
            if (ppctx) delete ppctx;
            ppctx = new preprocess::PreprocessorContext();
        }

        void DestroyPreprocessorContext() const {
            delete ppctx;
        }

        ~GlobalContextHandle() {
            if (ppctx) delete ppctx;
            for (const auto* task : tasks) {
                if (task->status == Running) {
                    spdlog::warn("Task {} is still running during destruction. Freeing its resources.", task->id);
                }
                if (task->ptr != 0)
                    free(reinterpret_cast<void*>(task->ptr));
            }
        }

    private:
        preprocess::PreprocessorContext* ppctx;
        std::vector<TaskHandle*> tasks;
        std::vector<int32_t> task_free_list;
        // std::atomic_int32_t task_id_counter{0};
    };

}