add_executable(fps_unlock_tests fps_unlock_tests.cpp)
target_link_libraries(fps_unlock_tests PRIVATE vopt::fps_unlock)

add_executable(pacing_tests pacing_tests.cpp)
target_link_libraries(pacing_tests PRIVATE vopt::frame_pacing)

add_test(NAME fps_unlock COMMAND fps_unlock_tests)
add_test(NAME pacing COMMAND pacing_tests)