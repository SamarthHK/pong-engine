//
// Created by munna-01 on 8/19/26.
//

#include "game.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstddef>

using namespace pong::state_files;

namespace pong {
    Game::Game(int ball_radius, int player_width, int player_height, int field_width, int field_height, int player_offset,
             float player_accel, float player_top_speed, float ball_accel, float collision_nudge) {
        ball.radius = ball_radius;
        const float raw_x = static_cast<float>((std::rand() % 200) - 100);
        const float raw_y = static_cast<float>((std::rand() % 200) - 100);
        const float raw_length = std::sqrt(raw_x * raw_x + raw_y * raw_y);
        const float normalized_x = nearly_zero(raw_length) ? 1.0f : raw_x / raw_length;
        const float normalized_y = nearly_zero(raw_length) ? 0.0f : raw_y / raw_length;
        ball.x_vel = normalized_x * ball.vel;
        ball.y_vel = normalized_y * ball.vel;

        initial_ball_x = ball.x;
        initial_ball_y = ball.y;
        initial_ball_x_vel = ball.x_vel;
        initial_ball_y_vel = ball.y_vel;
        initial_ball_vel = ball.vel;

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
        physics.collision_nudge = collision_nudge;

        initial_player_one_y = player_one.y;
        initial_player_two_y = player_two.y;
        initial_player_one_y_vel = player_one.y_vel;
        initial_player_two_y_vel = player_two.y_vel;

        reset();
    };

    StepResult Game::step(Move player_one_move, Move player_two_move) {
        move_player(player_one, p1_walls, player_one_move);
        move_player(player_two, p2_walls, player_two_move);

        //TODO: Implement ball movement and collision detection
    }

    void Game::reset() {
        ball.x = initial_ball_x;
        ball.y = initial_ball_y;
        ball.vel = initial_ball_vel;
        ball.x_vel = initial_ball_x_vel;
        ball.y_vel = initial_ball_y_vel;

        player_one.x = 0;
        player_one.y = initial_player_one_y;
        player_one.y_vel = initial_player_one_y_vel;

        player_two.x = 0;
        player_two.y = initial_player_two_y;
        player_two.y_vel = initial_player_two_y_vel;

        game_over = false;

        field_walls.assign_box_walls(0, 0, field.field_width, field.field_height);
        p1_walls.assign_box_walls(0, 0, player_one.width, player_one.height);
        p2_walls.assign_box_walls(0, 0, player_two.width, player_two.height);
    }

    void Game::move_player(PlayerData &player,Box &walls, Move move) {
        player.y_vel += static_cast<int>(move) * physics.player_accel;
        player.y_vel *= physics.player_accel;
        player.y += player.y_vel;

        int upper_bound = field.field_height/2;
        int lower_bound = field.field_height/-2;

        if (player.y < lower_bound) {
            player.y = lower_bound;
            player.y_vel = 0;
        }
        else if (player.y > upper_bound) {
            player.y = upper_bound;
            player.y_vel = 0;
        }

        walls.assign_box_walls(0, 0, player.width, player.height);
    }
}
