#include <../arrow_fn/DuckDBClient.hpp>
#include <iostream>
#include <arrow/c/bridge.h>
#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/dataset/api.h>
#include <duckdb/duckdb.h>

arrow::Status adbc_duck() {

    std::shared_ptr<arrow::Table> table;
    {
        db::DuckDBConnection db;
        auto success = db.ExecuteQueryNoReturn(R"(CREATE TABLE iris AS SELECT * from 'E:\C_Libs\duckdb\iri.parquet')").ok();
        //success = success && db.ExecuteQueryNoReturn(R"(CREATE TABLE titanic AS SELECT * from 'E:\C_Libs\duckdb\titanic.parquet')").ok();

        if (!success) {

        }

        if (!db.ExecuteQuery(R"(SELECT * from iris)", table).ok()) {
            std::cerr << "Error when creating table." << std::endl;
        }

        std::cout << "table 1 done." << std::endl;
    }
    /*{
        try {
            db::DuckDBConnection db;
            if (!db.ExecuteQuery(R"(SELECT * from titanic)", table).ok()) {
                std::cerr << "Error when creating table 2." << std::endl;
            }
        }
        catch (...) {
            std::cerr << "Query failed." << std::endl;
        }

        std::cout << "table 2 done." << std::endl;
    }*/

    ARROW_RETURN_NOT_OK(arrow::compute::Initialize());

    return arrow::Status::OK();
}

int main() {
    const auto stt = adbc_duck();

    return 0;
}