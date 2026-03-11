
find_package(antlr4-runtime CONFIG REQUIRED)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 1. THE ACTUAL MODULE: Build the parser as an Object Library or Static Library
# (An OBJECT library just compiles the .cpp files without linking them yet, 
# which is perfect for combining into a DLL later).
add_library(fluxpp OBJECT
    fluxppLexer.cpp 
    fluxppParser.cpp
    fluxppBaseListener.cpp
    fluxppBaseVisitor.cpp
    fluxppListener.cpp
    fluxppVisitor.cpp
    functions.cpp
    diagnose/diagnostic_impl.cpp
)
target_link_libraries(fluxpp PRIVATE CoreHeaders antlr4_static absl::flat_hash_map)
target_compile_definitions(fluxpp PRIVATE ANTLR4CPP_STATIC)

# 2. THE LOCAL TEST: Create an executable just for testing this module
add_executable(TestParser main_test.cpp)

# Link the test executable to our newly created module library
target_link_libraries(TestParser PRIVATE fluxpp antlr4_static CoreHeaders absl::flat_hash_map)







#---------------------------







#[[
    cmake_minimum_required(VERSION 3.15)
project(MyHugeProject)

# Set vcpkg triplet and MSVC runtime (from our previous setup)
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "" FORCE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# --- Internal Dependencies ---
# Create an INTERFACE library for your header-only core code
add_library(CoreHeaders INTERFACE)
target_include_directories(CoreHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common_includes)

# --- Subprojects ---
# Tell CMake to go look in these folders and run their CMakeLists.txt
add_subdirectory(antlr_parser_module)
add_subdirectory(some_other_module)

# --- Future Final Library ---
# When you are ready to build the whole thing into a DLL, you'll do it here
# add_library(FinalDynamicLib SHARED ...)
]]