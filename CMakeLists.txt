cmake_minimum_required(VERSION 3.16)
project(pong)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_library(pong_core src/game.cpp)
target_include_directories(pong_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(pong src/main.cpp)
target_link_libraries(pong PRIVATE pong_core)

add_executable(pong_tests tests/game_collision_tests.cpp)
target_link_libraries(pong_tests PRIVATE pong_core)

add_test(NAME pong_tests COMMAND pong_tests)
