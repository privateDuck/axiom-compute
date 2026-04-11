
find_package(Arrow CONFIG REQUIRED)
find_package(ArrowDataset REQUIRED)
find_package(Parquet REQUIRED)
find_package(AdbcDriverManager CONFIG REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# add_library(ExprEngine OBJECT file.cpp)
add_library(PreProcessor OBJECT infer_types.cpp source_validation.cpp)
add_library(duckdb_lib SHARED IMPORTED)
set_target_properties(duckdb_lib PROPERTIES
    IMPORTED_LOCATION "E:/axiom/atlas/lib/duckdb.lib"
    IMPORTED_IMPLIB "E:/axiom/atlas/lib/duckdb.lib"
)

target_link_libraries(PreProcessor PRIVATE CoreHeaders ARROWFN Arrow::arrow_static ArrowDataset::arrow_dataset_static
        Parquet::parquet_static duckdb_lib AdbcDriverManager::adbc_driver_manager_static)
target_compile_definitions(PreProcessor PRIVATE ARROW_STATIC ARROW_DS_STATIC
        PARQUET_STATIC ADBC_BUILD_STATIC)

# 2. THE LOCAL TEST: Create an executable just for testing this module
add_executable(TestPreProcessor main_test.cpp)

if(MSVC)
    target_compile_options(TestPreProcessor PRIVATE /arch:AVX2)
    target_compile_options(PreProcessor PRIVATE /arch:AVX2)
else()
    target_compile_options(TestPreProcessor PRIVATE -mavx2)
    target_compile_options(PreProcessor PRIVATE -mavx2)
endif()

# Link the test executable to our newly created module library
target_link_libraries(TestPreProcessor PRIVATE PreProcessor CoreHeaders ARROWFN Arrow::arrow_static ArrowDataset::arrow_dataset_static
        Parquet::parquet_static duckdb_lib AdbcDriverManager::adbc_driver_manager_static)
target_compile_definitions(TestPreProcessor PRIVATE ARROW_STATIC ARROW_DS_STATIC
        PARQUET_STATIC ADBC_BUILD_STATIC)