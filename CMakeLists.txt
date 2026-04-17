cmake_minimum_required(VERSION 3.20)

project(atlas LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_subdirectory(src)
add_subdirectory(ui)
add_subdirectory(runner)