#pragma once
#include <unordered_map>
#include "async_task.hpp"
#include <../include/spdlog/spdlog.h>
#include "../preprocess/preprocessor_ctx.hpp"

namespace top {

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
            tasks.at(id)->status.store(status, std::memory_order::release);
        }

        TaskStatus GetTaskStatus(const int32_t id) const {
            return tasks.at(id)->status.load(std::memory_order::acquire);
        }

        void FreeTaskHandle(const int32_t id) {
            if (id < tasks.size()) {
                auto* task = tasks.at(id);
                if (task->status == Running) {
                    spdlog::warn("Freeing a task handle that is still running: {}", id);
                }
                task_free_list.push_back(id);
                delete task;
                tasks.at(id) = nullptr;
            }
        }

        int32_t RequestTaskId() {
            const auto id = task_free_list.back();
            task_free_list.pop_back();
            return id;
        }

        AsyncTask* PushTask(AsyncTask* task) {
            tasks[task->id] = task;
            return task;
        }

        void CreatePreprocessorContext(const int src, const std::vector<std::string>& args) {
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
                delete task;
            }
        }

    private:
        preprocess::PreprocessorContext* ppctx;
        std::vector<AsyncTask*> tasks;
        std::vector<int32_t> task_free_list;
    };

}