
find_package(Arrow CONFIG REQUIRED)
find_package(ArrowDataset REQUIRED)
find_package(Parquet REQUIRED)
find_package(AdbcDriverManager CONFIG REQUIRED)
find_package(DuckDB CONFIG REQUIRED)

# add_library(ExprEngine OBJECT file.cpp)
add_library(ARROWFN OBJECT read_dataset.cpp string_df.cpp table_ops.cpp)
#[[add_library(duckdb_lib SHARED IMPORTED)
set_target_properties(duckdb_lib PROPERTIES
        IMPORTED_LOCATION "E:/atlas/lib/duckdb.lib"
        IMPORTED_IMPLIB "E:/atlas/lib/duckdb.lib"
)]]

target_link_libraries(ARROWFN PRIVATE CoreHeaders Arrow::arrow_shared ArrowDataset::arrow_dataset_shared
        Parquet::parquet_shared #[[duckdb_lib]] AdbcDriverManager::adbc_driver_manager_shared duckdb)

if(MSVC)
    target_compile_options(ARROWFN PRIVATE /arch:AVX2)
else()
    target_compile_options(ARROWFN PRIVATE -mavx2)
endif()