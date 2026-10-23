cmake_minimum_required(VERSION 4.3)
project(pong)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(pybind11)
pybind11_add_module(pong_module
        src/bindings/pong_module.cpp
        src/game.cpp
)
target_include_directories(pong_module PRIVATE src)

add_executable(pong src/main.cpp
        src/state_files/player_data.h
        src/state_files/ball_data.h
        src/state_files/umbrella_header.h
        src/state_files/field_data.h
        src/state_files/physics_data.h
        src/state_files/field_data.h
        src/game.cpp
        src/game.h
        src/move.h
		src/state_files/wall.h
)
find_package(SFML 3.0.2 REQUIRED COMPONENTS Graphics)
target_link_libraries(pong SFML::Graphics)
