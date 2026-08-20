//
// Created by munna-01 on 8/19/26.
//

#include "game.h"
#include <cmath>
#include <cstdlib>
#include <cmath>

using namespace pong::state_files;

namespace pong {
    Game::Game(int ball_radius, int player_width, int player_height, int field_width, int field_height, int player_offset,
             float player_accel, float player_top_speed, float ball_accel) {
        ball.radius = ball_radius;
        ball.angle = rand() % 2*pi;

        field.field_width = field_width;
        field.field_height = field_height;
        field.player_offset = player_offset;

        player_one.width = player_width;
        player_one.height = player_height;

        player_two.width = player_width;
        player_two.height = player_height;

        physics.player_top_speed = player_top_speed;
        physics.player_accel = player_accel;
        physics.ball_accel = ball_accel;

        field_walls.assign_walls(0, 0, field_width, field_height);
        move_player(player_one, p1_walls, Move::NONE);
        move_player(player_two, p2_walls, Move::NONE);
    };

    void Game::step(Move player_one_move, Move player_two_move) {
        //Ball movement logic first
        ball.x += std::cos(ball.angle) * ball.vel;
        ball.y += std::sin(ball.angle) * ball.vel;

        //Paddle movement logic:
        move_player(player_one, p1_walls, player_one_move);
        move_player(player_two, p2_walls, player_two_move);
        //Now do collision checks
    }

    void Game::move_player(PlayerData &player,WallGroup &walls, Move move) {
        player.y += static_cast<int>(move) * physics.player_accel;
        player.y *= physics.player_accel;
        walls.assign_walls(0, 0, player.width, player.height);
    }
}
