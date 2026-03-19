set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(hwy CONFIG REQUIRED)

add_library(ExprEngine OBJECT
        kernels/fp_64.cpp
        kernels/eig.cpp
        kernels/avx2.cpp
        kernels/i64.cpp
)

target_link_libraries(ExprEngine PRIVATE CoreHeaders hwy::hwy)

# 2. THE LOCAL TEST: Create an executable just for testing this module
add_executable(TestExprEngine main_test.cpp)


if(MSVC)
    target_compile_options(TestExprEngine PRIVATE /arch:AVX2)
    target_compile_options(ExprEngine PRIVATE /arch:AVX2)
else()
    target_compile_options(TestExprEngine PRIVATE -mavx2)
    target_compile_options(ExprEngine PRIVATE -mavx2)
endif()
# Link the test executable to our newly created module library
target_link_libraries(TestExprEngine PRIVATE ExprEngine CoreHeaders hwy::hwy)