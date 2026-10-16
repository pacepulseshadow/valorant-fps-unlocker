add_library(shared_lib STATIC
    log.cpp
    process_scan.cpp
    paths.cpp
    json_lite.cpp)
target_include_directories(shared_lib PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(shared_lib PRIVATE shell32 ole32)
add_library(v