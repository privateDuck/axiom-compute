#include "preprocessor_ctx.hpp"
#include "source_validation.hpp"
#include "infer_types.hpp"
#include <nlohmann/json.hpp>
#include <filesystem>
#include "../arrow_fn/read_dataset.hpp"
#include "type_casts.hpp"
#include "../arrow_fn/table_ops.hpp"

namespace preprocess {
    SourceValidationResult validate_source(const SourceType source, const std::string& args) {
        nlohmann::json json = nlohmann::json::parse(args);
        arrow::Status status;
        afn::RowWiseStringDF df;
        switch (source) {
            case SourceType::LocalFile:
                status = validate_local(json["path"].get<std::string>(), df);
                break;
            case SourceType::DatasetDirectory:
                status = validate_directory(json["path"].get<std::string>(), json["file_type"].get<std::string>()[0], df);
                break;
            case SourceType::CombineFiles:
                status = validate_file_join(json["files"].get<std::vector<std::string>>(), df);
                break;
            case SourceType::RemoteURI:
                status = Validate_remote_uri(json["path"].get<std::string>(), df);
                break;
            case SourceType::DatabaseConnection:
                status = validate_db_query(json["connection_string"].get<std::string>(), df);
                break;
            default:
                break;
        }
        if (!status.ok()) {
            return SourceValidationResult(status.message());
        }
        return SourceValidationResult(df);
    }

    TypeInferenceResult import_and_infer_types(PreprocessorContext* ctx, const SourceType source, const std::string& import_args) {
        nlohmann::json json = nlohmann::json::parse(import_args);
        arrow::Result<std::shared_ptr<arrow::Table>> res;
        switch (source) {
            case SourceType::LocalFile:
                res = afn::ReadEagerFile(json["path"].get<std::string>());
                break;
            case SourceType::DatasetDirectory:
                res = afn::ScanEagerDirectory(json["file_type"].get<std::string>(), json["path"].get<std::string>());
                break;
            case SourceType::CombineFiles:
                res = afn::ReadJoinedFileSet(json["files"].get<std::vector<std::string>>(), json["query"].get<std::string>());
                break;
            case SourceType::RemoteURI:
                res = afn::ReadEagerFileURI(json["uri"].get<std::string>());
                break;
            case SourceType::DatabaseConnection:
                res = afn::ReadDatabaseConnection(json["connection_string"].get<std::string>(), json["query"].get<std::string>());
                break;
            default:
                throw std::runtime_error("Unsupported source type for import and infer.");
        }
        if (res.ok()) {
            ctx->table = res.ValueOrDie();
        }
        return infer_types_of_table(ctx->table);
    }

    // convert/coerce each column into the specified type
    // if coercion failed, set the value to null
    // count the nulls
    // perform data quality conforms: deduplication (row wise), zero variance (any-t) column, all null (any-t), var factor <= 10 (string-t)
    void type_cast_and_null_check(PreprocessorContext *ctx, const std::string &type_infer_map) {
        nlohmann::json json = nlohmann::json::parse(type_infer_map);
        std::unordered_map<std::string, arrow::Type::type> type_map;
        std::unordered_map<std::string, std::string> additional_data_map;
        for (const auto& [key, value] : json["types"].items()) {
            const auto value_str = value.get<std::string>();
            arrow::Type::type type;
            switch (value_str[0]) {
                case 'i':
                    type = arrow::Type::type::INT64;
                    break;
                case 'r':
                    type = arrow::Type::type::DOUBLE;
                    break;
                case 'b':
                    type = arrow::Type::type::BOOL;
                    break;
                case 'd':
                    type = arrow::Type::type::TIMESTAMP;
                    break;
                case 's':
                    type = arrow::Type::type::STRING;
                    break;
                default:
                    throw std::runtime_error("Unsupported type in type inference map: " + value_str);
            }
            type_map.insert_or_assign(key, type);
        }
        for (const auto& [key, value] : json["additional"].items()) {
            const auto value_str = value.get<std::string>();
            additional_data_map.insert_or_assign(key, value_str);
        }

        const auto status = CastOrCoerceTable(ctx->table, type_map, additional_data_map);
        if (!status.ok()) {
            // TODO: Handle the case
        }

        auto res = afn::DropDuplicates(ctx->table);
        if (!res.ok()) {
            // TODO: Handle the case
        }
    }
}
