cmake_minimum_required(VERSION 3.20)

project(atlas LANGUAGES CXX C)

# --- GLOBAL SETTINGS STAY HERE ---
# By keeping these at the root, your 'ui' and 'runner' projects
# automatically inherit C++20 and your MSVC runtime settings.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# --- FIND QT HERE ---
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# --- ADD SUBDIRECTORIES ---
add_subdirectory(src)
add_subdirectory(ui)
add_subdirectory(runner)