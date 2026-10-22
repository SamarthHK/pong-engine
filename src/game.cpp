//
// Created by munna-01 on 8/19/26.
//

#include "game.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <iostream>

using namespace pong::state_files;

namespace pong {
    Game::Game(int ball_radius, int player_width, int player_height, int field_width, int field_height, int player_offset,
             float player_accel, float player_top_speed, float ball_accel, float ball_vel) {
        ball.radius = ball_radius;
        ball.vel = ball_vel;

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

        reset();
    };

    StepResult Game::step(Move player_one_move, Move player_two_move, float delta_time) {
        move_player(player_one, p1_walls, player_one_move,delta_time);
        move_player(player_two, p2_walls, player_two_move,delta_time);
        ball.x += ball.x_vel * delta_time;
        ball.y += ball.y_vel * delta_time;
        //TODO: Implement ball movement and collision detection
        return StepResult{
            ball.x,
            ball.y,
            player_one.x,
            player_one.y,
            player_two.x,
            player_two.y,
            game_over
        };
    }

    void Game::reset() {
        //Assigning random initial velocity to the ball with a random direction keeping magnitude of velocity constant
        const float rand_x = static_cast<float>(std::rand() % 100 + 100)/200.0f;
        const float rand_y = static_cast<float>(std::rand() % 200)/200.0f;
        const float raw_length = std::sqrt(rand_x * rand_x + rand_y * rand_y);
        const float ratio = ball.vel / raw_length;
        ball.x_vel = ratio * rand_x;
        ball.y_vel = ratio * rand_y;

        ball.x = field.field_width/2;
        ball.y = field.field_height/2;

        //assigning random direction to the ball velocity, one of 4 quadrants, by randomly flipping the signs of x_vel and y_vel
        const int rand_dir = std::rand() % 4;
        if (rand_dir == 1) {
            ball.x_vel *= -1;
        }else if (rand_dir == 2) {
            ball.y_vel *= -1;
        }else if (rand_dir == 3) {
            ball.x_vel *= -1;
            ball.y_vel *= -1;
        }

        player_one.y = field.field_height/2;
        player_one.x = field.player_offset;
        player_one.y_vel = 0;

        player_two.y = field.field_height/2;
        player_two.x = field.field_width - field.player_offset;
        player_two.y_vel = 0;
        game_over = false;

        field_walls.assign_box_walls(0, 0, field.field_width, field.field_height);
        p1_walls.assign_box_walls(player_one.x, player_one.y, player_one.width, player_one.height);
        p2_walls.assign_box_walls(player_two.x, player_two.y, player_two.width, player_two.height);
    }

    void Game::move_player(PlayerData &player,Box &walls, Move move, float delta_time) {
        player.y_vel += physics.player_accel * delta_time * static_cast<float>(move) * -1.0f; //-1 because the y-axis is inverted in the game
        player.y_vel *= physics.player_friction;
        player.y += player.y_vel * delta_time;

        int upper_bound = player.height/2;
        int lower_bound = field.field_height-player.height/2;

        if (player.y > lower_bound) {
            player.y = lower_bound;
            player.y_vel = 0;
        }
        else if (player.y < upper_bound) {
            player.y = upper_bound;
            player.y_vel = 0;
        }

        walls.assign_box_walls(player.x, player.y, player.width, player.height);
    }
}
