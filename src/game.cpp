//
// Created by munna-01 on 8/19/26.
//

#include "game.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
        move_ball(delta_time);
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
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        //Assigning random initial velocity to the ball with a random direction keeping magnitude of velocity constant
        const float rand_x = static_cast<float>(std::rand() % 100 + 100)/200.0f;
        const float rand_y = static_cast<float>(std::rand() % 200)/200.0f;
        const float raw_length = std::sqrt(rand_x * rand_x + rand_y * rand_y);
        const float ratio = ball.vel / raw_length;
        ball.x_vel = ratio * rand_x;
        ball.y_vel = ratio * rand_y;

        ball.x = field.field_width / 2.0f;
        ball.y = field.field_height / 2.0f;

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

        player_one.x = field.player_offset;
        player_one.y = (field.field_height - player_one.height) / 2.0f;
        player_one.y_vel = 0;

        player_two.x = field.field_width - field.player_offset - player_two.width;
        player_two.y = (field.field_height - player_two.height) / 2.0f;
        player_two.y_vel = 0;
        game_over = false;

        field_walls.assign_box_walls(0, 0, field.field_width, field.field_height, false);
        p1_walls.assign_box_walls(player_one.x, player_one.y, player_one.width, player_one.height, false);
        p2_walls.assign_box_walls(player_two.x, player_two.y, player_two.width, player_two.height, false);
    }

    void Game::move_ball(float delta_time) {
        float remaining_time = delta_time;

        while (remaining_time > 0.0f) {
            const float old_ball_x = ball.x;
            const float old_ball_y = ball.y;
            const float next_ball_x = old_ball_x + ball.x_vel * remaining_time;
            const float next_ball_y = old_ball_y + ball.y_vel * remaining_time;

            const Wall* hit_wall = nullptr;
            bool hit_vertical = false;
            float collision_time = remaining_time;
            float target_position = 0.0f;

            for (const auto* wall : walls) {
                if (!wall) {
                    continue;
                }

                const float min_x = std::min(wall->x1, wall->x2);
                const float max_x = std::max(wall->x1, wall->x2);
                const float min_y = std::min(wall->y1, wall->y2);
                const float max_y = std::max(wall->y1, wall->y2);

                if (wall->orientation == WallOrientation::Vertical) {
                    if (ball.x_vel > 0.0f) {
                        float t_hit = (wall->x1 - ball.radius - old_ball_x) / ball.x_vel;
                        if (t_hit >= -1e-6f && t_hit <= remaining_time + 1e-6f && t_hit < collision_time) {
                            const float y_at_hit = old_ball_y + ball.y_vel * t_hit;
                            if (y_at_hit + ball.radius >= min_y && y_at_hit - ball.radius <= max_y) {
                                collision_time = t_hit;
                                hit_wall = wall;
                                hit_vertical = true;
                                target_position = wall->x1 - ball.radius;
                            }
                        }
                    }
                    else if (ball.x_vel < 0.0f) {
                        float t_hit = (wall->x1 + ball.radius - old_ball_x) / ball.x_vel;
                        if (t_hit >= -1e-6f && t_hit <= remaining_time + 1e-6f && t_hit < collision_time) {
                            const float y_at_hit = old_ball_y + ball.y_vel * t_hit;
                            if (y_at_hit + ball.radius >= min_y && y_at_hit - ball.radius <= max_y) {
                                collision_time = t_hit;
                                hit_wall = wall;
                                hit_vertical = true;
                                target_position = wall->x1 + ball.radius;
                            }
                        }
                    }
                }
                else {
                    if (ball.y_vel > 0.0f) {
                        float t_hit = (wall->y1 - ball.radius - old_ball_y) / ball.y_vel;
                        if (t_hit >= -1e-6f && t_hit <= remaining_time + 1e-6f && t_hit < collision_time) {
                            const float x_at_hit = old_ball_x + ball.x_vel * t_hit;
                            if (x_at_hit + ball.radius >= min_x && x_at_hit - ball.radius <= max_x) {
                                collision_time = t_hit;
                                hit_wall = wall;
                                hit_vertical = false;
                                target_position = wall->y1 - ball.radius;
                            }
                        }
                    }
                    else if (ball.y_vel < 0.0f) {
                        float t_hit = (wall->y1 + ball.radius - old_ball_y) / ball.y_vel;
                        if (t_hit >= -1e-6f && t_hit <= remaining_time + 1e-6f && t_hit < collision_time) {
                            const float x_at_hit = old_ball_x + ball.x_vel * t_hit;
                            if (x_at_hit + ball.radius >= min_x && x_at_hit - ball.radius <= max_x) {
                                collision_time = t_hit;
                                hit_wall = wall;
                                hit_vertical = false;
                                target_position = wall->y1 + ball.radius;
                            }
                        }
                    }
                }
            }

            if (hit_wall == nullptr) {
                ball.x = next_ball_x;
                ball.y = next_ball_y;
                return;
            }

            ball.x = old_ball_x + ball.x_vel * collision_time;
            ball.y = old_ball_y + ball.y_vel * collision_time;

            if (hit_vertical) {
                ball.x = target_position;
                ball.x_vel *= -1.0f;
                ball.x_vel *= physics.ball_accel;
            }
            else {
                ball.y = target_position;
                ball.y_vel *= -1.0f;
                ball.y_vel *= physics.ball_accel;
            }

            remaining_time -= collision_time;
            if (remaining_time <= 1e-6f) {
                return;
            }
        }
    }

    void Game::move_player(PlayerData &player,Box &walls, Move move, float delta_time) {
        player.y_vel += physics.player_accel * delta_time * static_cast<float>(move) * -1.0f; //-1 because the y-axis is inverted in the game
        player.y_vel *= physics.player_friction;
        player.y += player.y_vel * delta_time;

        const float min_y = 0.0f;
        const float max_y = static_cast<float>(field.field_height - player.height);

        if (player.y < min_y) {
            player.y = min_y;
            player.y_vel = 0;
        }
        else if (player.y > max_y) {
            player.y = max_y;
            player.y_vel = 0;
        }

        walls.assign_box_walls(player.x, player.y, player.width, player.height, false);
    }
}
