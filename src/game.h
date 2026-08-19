//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "./state_files/umbrella_header.h"
#include "./move.h"

using namespace pong::state_files;

namespace pong {
    class Game {
    public:
        BallData ball;
        FieldData field;
        PlayerData player_one, player_two;
        PhysicsData physics;
        Game(int ball_radius = 5, int player_width = 10, int player_height = 40, int field_width = 120, int field_height = 80, int player_offset = 30, float player_accel = 3, float player_top_speed = 10, float ball_accel = 1.05);
        void step(Move player_one_move, Move player_two_move);
    };
}

#endif //PONG_GAME_H
