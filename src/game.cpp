//
// Created by munna-01 on 8/19/26.
//

#include "game.h"
#include <cstdlib>
#include <math.h>

using namespace pong::state_files;

namespace pong {
    Game::Game(int ball_radius, int player_width, int player_height, int field_width, int field_height, int player_offset,
             float player_accel, float player_top_speed, float ball_accel) {
        ball.radius = ball_radius;
        ball.angle = rand() % 360;

        field.field_width = field_width;
        field.field_height = field_height;
        field.player_offset = player_offset;

        player_one.width = player_width;
        player_one.height = field_height;

        player_two.width = field_width;
        player_two.height = field_height;

        physics.player_top_speed = player_top_speed;
        physics.player_accel = player_accel;
        physics.ball_accel = ball_accel;
    };

    void Game::step(Move player_one_move, Move player_two_move) {
        //Ball movement logic first
        int ball_x_movement, ball_y_movement;


    }


}