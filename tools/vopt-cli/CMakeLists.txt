add_executable(vopt-cli main.cpp)
target_link_libraries(vopt-cli PRIVATE
    vopt::config_layer
    vopt::fps_unlock
    vopt::shared_lib)
target_compile_definitions(vopt-cli PRIVATE VOPT_CLI=1)