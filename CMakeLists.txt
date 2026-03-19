cmake_minimum_required(VERSION 3.20)

# We include C because you have sqlite3.c
project(atlas LANGUAGES CXX C)

# --- 1. CONFIGURATION ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


add_library(CoreHeaders INTERFACE IMPORTED)
target_include_directories(CoreHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# --- 2. DEPENDENCIES ---
# A. LibTorch
# CLion will look for the library path defined in Settings (see Step 2 below)
# find_package(Torch REQUIRED)
find_package(hwy CONFIG REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)
find_package(Arrow CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)

# SAFETY CHECK: If the user tries to build Release but LibTorch is Debug-only
#[[if(NOT MSVC_TOOLSET_VERSION)
    # Check if we are linking against a debug library (rough check)
    get_target_property(TORCH_LOC torch LOCATION)
    if("${TORCH_LOC}" MATCHES "debug" AND "${CMAKE_BUILD_TYPE}" MATCHES "Release")
        message(WARNING "WARNING: You are building in Release mode but LibTorch appears to be Debug. Linker errors may occur.")
    endif()
endif()
]]
add_subdirectory(src/scripting/fluxpp)
add_subdirectory(src/exec/ExprEngine)

add_library(FinalAtlas STATIC
        $<TARGET_OBJECTS:fluxpp>
        # $<TARGET_OBJECTS:another_module>
)
target_link_libraries(FinalAtlas PUBLIC CoreHeaders antlr4-runtime)

# Link LibTorch (Includes all headers/flags automatically)
# target_link_libraries(atlas PRIVATE "${TORCH_LIBRARIES}")
# target_link_libraries(atlas PRIVATE
#         Arrow::arrow_shared      # Use shared library for Arrow
#         re2::re2                 # Regular expressions
# )

target_link_libraries(FinalAtlas PRIVATE
        absl::strings
        absl::flat_hash_map
        absl::flat_hash_set
        absl::time
        absl::random_random
)

# Link Local Libraries (DuckDB, etc.)
# Assuming 'lib' folder is at E:/axiom/atlas/lib
target_link_directories(FinalAtlas PRIVATE "lib")
target_link_libraries(FinalAtlas PRIVATE "duckdb")


# --- 6. POST-BUILD (DLL COPY) ---
# CLion runs the exe from a build folder, so we must copy DLLs there.
# This command works for both VS and Ninja generators.
add_custom_command(TARGET FinalAtlas POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/libtorch/lib/torch.dll"
    "C:/libtorch/lib/torch_cpu.dll"
    "C:/libtorch/lib/c10.dll"
    # Also copy nvToolsExt if you eventually use CUDA
    # "C:/libtorch/lib/nvToolsExt64_1.dll" 
    $<TARGET_FILE_DIR:FinalAtlas>
    COMMENT "Copying LibTorch DLLs..."
)