cmake_minimum_required(VERSION 4.3)
project(pong)

set(CMAKE_CXX_STANDARD 20)

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
        src/wall.h
)
