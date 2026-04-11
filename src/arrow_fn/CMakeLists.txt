
find_package(Arrow CONFIG REQUIRED)
find_package(ArrowDataset REQUIRED)
find_package(Parquet REQUIRED)
find_package(AdbcDriverManager CONFIG REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# add_library(ExprEngine OBJECT file.cpp)
add_library(ARROWFN OBJECT read_dataset.cpp string_df.cpp table_ops.cpp)
add_library(duckdb_lib SHARED IMPORTED)
set_target_properties(duckdb_lib PROPERTIES
        IMPORTED_LOCATION "E:/axiom/atlas/lib/duckdb.lib"
        IMPORTED_IMPLIB "E:/axiom/atlas/lib/duckdb.lib"
)

target_link_libraries(ARROWFN PRIVATE CoreHeaders Arrow::arrow_static ArrowDataset::arrow_dataset_static
        Parquet::parquet_static duckdb_lib AdbcDriverManager::adbc_driver_manager_static)
target_compile_definitions(ARROWFN PRIVATE ARROW_STATIC ARROW_DS_STATIC
        PARQUET_STATIC ADBC_BUILD_STATIC)

if(MSVC)
    target_compile_options(ARROWFN PRIVATE /arch:AVX2)
else()
    target_compile_options(ARROWFN PRIVATE -mavx2)
endif()