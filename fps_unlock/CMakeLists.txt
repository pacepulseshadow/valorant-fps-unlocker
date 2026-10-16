add_library(fps_unlock STATIC
    fps_unlocker.cpp
    ini_writer.cpp)
target_include_directories(fps_unlock PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(fps_unlock PRIVATE vopt::shared_lib)
add_library(vopt::fps_unlock ALIAS fps_unlock)