#include "preprocessor_ctx.hpp"
#include "source_validation.hpp"
#include <nlohmann/json.hpp>
#include <filesystem>

namespace preprocess {
    afn::RowWiseStringDF validate_source(const SourceType source, const std::string& args) {
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
            throw std::runtime_error("Actually handle the fucking error bro. This is the last line of defense");
        }
        return df;
    }

    afn::RowWiseStringDF import_and_infer_types(PreprocessorContext* ctx, SourceType source, const std::string& import_args) {

    }
}
