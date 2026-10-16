add_library(overlay_core STATIC overlay_host.cpp)
target_include_directories(overlay_core PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(overlay_core PRIVATE vopt::shared_lib user32 gdi32 dwmapi)
add_library(vopt::overlay_core ALIAS overlay_core)