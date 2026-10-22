//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "./state_files/umbrella_header.h"
#include "./move.h"
#include "state_files/wall.h"

using namespace pong::state_files;

namespace pong {
    struct StepResult {
        float ball_x = 0;
        float ball_y = 0;
        float player_one_x = 0;
        float player_one_y = 0;
        float player_two_x = 0;
        float player_two_y = 0;
        bool game_over = false;
    };

    class Game {
    public:
        float pi = 3.14159;
        Box field_walls, p1_walls, p2_walls;
        Wall* walls[12] = {&field_walls.left_wall, &field_walls.right_wall, &field_walls.top_wall, &field_walls.bottom_wall, &p1_walls.left_wall, &p1_walls.right_wall, &p1_walls.top_wall, &p1_walls.bottom_wall, &p2_walls.left_wall, &p2_walls.right_wall, &p2_walls.top_wall, &p2_walls.bottom_wall};
        float t[12];
        BallData ball;
        FieldData field;
        PlayerData player_one, player_two;
        PhysicsData physics;
        bool game_over = false;
        Game(int ball_radius = 5, int player_width = 10, int player_height = 40, int field_width = 120, int field_height = 80, int player_offset = 30, float player_accel = 3, float player_top_speed = 10, float ball_accel = 1.05, float ball_vel = 10);
        StepResult step(Move player_one_move, Move player_two_move, float delta_time);
        void reset();
        void move_player(PlayerData &player,Box &walls, Move move, float delta_time);
    };
}

#endif //PONG_GAME_H
