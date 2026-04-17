find_package(hwy CONFIG REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)
find_package(Arrow CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)

# --- 2. DEFINE HEADERS & SUBDIRECTORIES ---
add_library(CoreHeaders INTERFACE IMPORTED)
# NOTE: Path changed. Removed the "src/" prefix since we are already in src/
target_include_directories(CoreHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# NOTE: Paths changed. Removed "src/" prefixes.
add_subdirectory(scripting/fluxpp)
add_subdirectory(exec/ExprEngine)
add_subdirectory(arrow_fn)
add_subdirectory(preprocess)

# --- 3. BUILD THE CORE LIBRARY ---
add_library(FinalAtlas STATIC
        $<TARGET_OBJECTS:fluxpp>
)


target_link_libraries(FinalAtlas PUBLIC CoreHeaders antlr4-runtime)
target_link_libraries(FinalAtlas PRIVATE
        absl::strings
        absl::flat_hash_map
        absl::flat_hash_set
        absl::time
        absl::random_random
)

target_compile_definitions(FinalAtlas PRIVATE
        ABSL_CONSUME_DLL
)

# NOTE: Crucial path change here for your external lib folder!
# Use CMAKE_SOURCE_DIR to point to the root /lib directory, 
# otherwise CMake looks for src/lib.
# target_link_directories(FinalAtlas PRIVATE "${CMAKE_SOURCE_DIR}/lib")
# target_link_libraries(FinalAtlas PRIVATE "duckdb")