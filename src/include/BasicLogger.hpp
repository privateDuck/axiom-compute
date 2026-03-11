#pragma once

#include <string>
#include <vector>
#include <format>
#include "antlr/antlr4-runtime.h"

namespace aux {


	enum class LogType {
		INFO,
		WARNING,
		CRITICAL,
		ERROR
	};

	struct LogEntry {
		int line;
		int column;
		LogType type;
		std::string message;

		LogEntry() : line(-1), column(-1), type(LogType::INFO), message("") {}
		LogEntry(int line, int column, LogType type, const std::string& message) : line(line), column(column), type(type), message(message) {}

		std::string ToString() const {
			return std::format("({}:{}) [{}:] {}", line, column, GetTypeString(type), message);
		}

	private:
		static constexpr std::string GetTypeString(LogType type) {
			switch (type) {
			case LogType::INFO:
				return "INFO";
			case LogType::WARNING:
				return "WARNING";
			case LogType::CRITICAL:
				return "CRITICAL";
			case LogType::ERROR:
				return "ERROR";
			default:
				return "UNKNOWN";
			}
		}
	};

	struct ErrorCode {
		std::string fmt_msg;
		std::string fmt_desc;
	};

	class BasicLogger {
	public:
		std::vector<LogEntry> entries;

		explicit BasicLogger() {}

		template<typename... Args>
		void LogWarning(antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::WARNING, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogError(antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::ERROR, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogInfo(antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::INFO, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogCritical(antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::CRITICAL, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
		}

		void Log(int line, int column, LogType type, const std::string& message) {
			entries.emplace_back(line, column, type, message);
		}

		// Common checks
		template<typename... Args>
		void CheckError(bool condition, antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			if (condition) {
				entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::ERROR, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
			}
		}

		template<typename... Args>
		void CheckWarning(bool condition, antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			if (condition) {
				entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::WARNING, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
			}
		}

		void GenerateMisalignedDereferenceWarning(antlr4::ParserRuleContext* ctx) {
			LogWarning(ctx, "Misaligned dereference");
		}

		[[nodiscard]] std::string GetLog() const {
			std::string log = "";
			for (auto& entry : entries) {
				log += entry.ToString() + "\n";
			}
			return log;
		}
	};

	class CodeLogger {
	public:
		std::vector<LogEntry> entries;

		explicit CodeLogger(const std::unordered_map<std::string, ErrorCode>& code_map) : error_code_map(code_map) {}

		template<typename... Args>
		void LogWarning(antlr4::ParserRuleContext* ctx, const std::string& code, Args&&... args) {
			const auto& err = error_code_map[code];
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::WARNING, std::vformat(err.fmt_desc, std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogError(antlr4::ParserRuleContext* ctx, const std::string& code, Args&&... args) {
			const auto& err = error_code_map[code];
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::ERROR, std::vformat(err.fmt_desc, std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogInfo(antlr4::ParserRuleContext* ctx,  const std::string& code, Args&&... args) {
			const auto& err = error_code_map[code];
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::INFO, std::vformat(err.fmt_desc, std::make_format_args(args...)));
		}

		template<typename... Args>
		void LogCritical(antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::CRITICAL, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
		}

		void Log(int line, int column, LogType type, const std::string& message) {
			entries.emplace_back(line, column, type, message);
		}

		// Common checks
		template<typename... Args>
		void CheckError(bool condition, antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			if (condition) {
				entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::ERROR, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
			}
		}

		template<typename... Args>
		void CheckWarning(bool condition, antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
			if (condition) {
				entries.emplace_back(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), LogType::WARNING, std::vformat(fmt_msg.get(), std::make_format_args(args...)));
			}
		}

		[[nodiscard]] std::string GetLog() const {
			std::string log;
			for (auto& entry : entries) {
				log += entry.ToString() + "\n";
			}
			return log;
		}
	private:
		std::unordered_map<std::string, ErrorCode> error_code_map;
	};
};