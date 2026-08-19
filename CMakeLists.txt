cmake_minimum_required(VERSION 4.3)
project(pong)

set(CMAKE_CXX_STANDARD 20)

add_executable(pong src/main.cpp
        src/state_files/player_data.cpp
        src/state_files/player_data.h
        src/state_files/ball_data.cpp
        src/state_files/ball_data.h
        src/state_files/umbrella_header.h
        src/state_files/feild_data.cpp
        src/state_files/feild_data.h
)
