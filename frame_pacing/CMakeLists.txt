add_library(frame_pacing STATIC pacing_engine.cpp)
target_include_directories(frame_pacing PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(frame_pacing PRIVATE vopt::shared_lib)
add_library(vopt::frame_pacing ALIAS frame_pacing)