set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(arrow CONFIG REQUIRED)

# add_library(ExprEngine OBJECT file.cpp)


target_link_libraries(PreProcessor PRIVATE CoreHeaders arrow::arrow)

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
target_link_libraries(TestPreProcessor PRIVATE PreProcessor CoreHeaders arrow::arrow)