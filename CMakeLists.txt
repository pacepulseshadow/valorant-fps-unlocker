cmake_minimum_required(VERSION 3.28)
project(valorant_fps_unlocker VERSION 0.6.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus /utf-8)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

add_subdirectory(fps_unlock)
add_subdirectory(frame_pacing)
add_subdirectory(overlay_core)
add_subdirectory(config_layer)
add_subdirectory(shared_lib)
add_subdirectory(bootstrap)

option(VOPT_BUILD_CLI "Build the vopt-cli diagnostic tool" ON)
if (VOPT_BUILD_CLI)
    add_subdirectory(tools/vopt-cli)
endif()

option(VOPT_BUILD_TESTS "Build unit tests" OFF)
if (VOPT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()