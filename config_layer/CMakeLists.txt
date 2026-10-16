add_library(config_layer STATIC config_loader.cpp)
target_include_directories(config_layer PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(config_layer PRIVATE vopt::shared_lib)
add_library(vopt::config_layer ALIAS config_layer)