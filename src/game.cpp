//
// Created by munna-01 on 8/19/26.
//

#include "game.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstddef>

using namespace pong::state_files;

namespace {
    struct Vec2 {
        float x = 0;
        float y = 0;
    };

    struct Rect {
        float min_x = 0;
        float max_x = 0;
        float min_y = 0;
        float max_y = 0;
    };

    struct CollisionHit {
        const pong::Wall *horizontal_wall = nullptr;
        const pong::Wall *vertical_wall = nullptr;
        float t = 1.0f;
        bool found = false;
    };

    constexpr float collision_tolerance = 0.00001f;

    Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs) {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    Vec2 operator*(const Vec2 &lhs, float rhs) {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    Vec2 operator*(float lhs, const Vec2 &rhs) {
        return rhs * lhs;
    }

    bool nearly_zero(float value) {
        return std::fabs(value) <= collision_tolerance;
    }

    Rect expanded_wall_bounds(const pong::Wall &wall, float radius) {
        return {
            std::min(static_cast<float>(wall.x1), static_cast<float>(wall.x2)) - radius,
            std::max(static_cast<float>(wall.x1), static_cast<float>(wall.x2)) + radius,
            std::min(static_cast<float>(wall.y1), static_cast<float>(wall.y2)) - radius,
            std::max(static_cast<float>(wall.y1), static_cast<float>(wall.y2)) + radius
        };
    }

    bool point_in_rect_inclusive(const Vec2 &point, const Rect &rect) {
        return point.x >= rect.min_x && point.x <= rect.max_x && point.y >= rect.min_y && point.y <= rect.max_y;
    }

    bool point_in_rect_strict(const Vec2 &point, const Rect &rect) {
        return point.x > rect.min_x && point.x < rect.max_x && point.y > rect.min_y && point.y < rect.max_y;
    }

    bool segment_hits_rect(const Vec2 &start, const Vec2 &travel, const Rect &rect, float *hit_t) {
        float t_min = 0.0f;
        float t_max = 1.0f;

        auto clip = [&](float start_axis, float travel_axis, float min_axis, float max_axis) {
            if (nearly_zero(travel_axis)) {
                return start_axis >= min_axis && start_axis <= max_axis;
            }

            const float inverse = 1.0f / travel_axis;
            float t1 = (min_axis - start_axis) * inverse;
            float t2 = (max_axis - start_axis) * inverse;

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            t_min = std::max(t_min, t1);
            t_max = std::min(t_max, t2);
            return t_min <= t_max;
        };

        if (!clip(start.x, travel.x, rect.min_x, rect.max_x)) {
            return false;
        }

        if (!clip(start.y, travel.y, rect.min_y, rect.max_y)) {
            return false;
        }

        if (t_max < 0.0f || t_min > 1.0f) {
            return false;
        }

        *hit_t = std::max(0.0f, t_min);
        return true;
    }

    bool wall_contains_point(const pong::Wall &wall, const Vec2 &point, float radius) {
        return point_in_rect_inclusive(point, expanded_wall_bounds(wall, radius));
    }

    bool touches_any_other_wall(const Vec2 &point, float radius, const pong::Wall *const *walls, std::size_t wall_count, const pong::Wall *ignore_a, const pong::Wall *ignore_b) {
        for (std::size_t index = 0; index < wall_count; ++index) {
            const pong::Wall *wall = walls[index];

            if (wall == nullptr || wall == ignore_a || wall == ignore_b) {
                continue;
            }

            if (wall_contains_point(*wall, point, radius)) {
                return true;
            }
        }

        return false;
    }

    CollisionHit find_closest_hit(const Vec2 &start, const Vec2 &travel, float radius, const pong::Wall *const *walls, std::size_t wall_count) {
        CollisionHit best_hit;

        for (std::size_t index = 0; index < wall_count; ++index) {
            const pong::Wall *wall = walls[index];

            if (wall == nullptr) {
                continue;
            }

            float hit_t = 1.0f;
            if (!segment_hits_rect(start, travel, expanded_wall_bounds(*wall, radius), &hit_t)) {
                continue;
            }

            if (!best_hit.found || hit_t < best_hit.t - collision_tolerance) {
                best_hit = {};
                best_hit.found = true;
                best_hit.t = hit_t;
            }

            if (!best_hit.found || std::fabs(hit_t - best_hit.t) > collision_tolerance) {
                continue;
            }

            if (wall->orientation == pong::WallOrientation::Horizontal) {
                best_hit.horizontal_wall = wall;
            } else {
                best_hit.vertical_wall = wall;
            }
        }

        return best_hit;
    }

    Vec2 reflect_velocity(const Vec2 &velocity, const CollisionHit &hit) {
        Vec2 reflected = velocity;

        if (hit.horizontal_wall != nullptr) {
            reflected.y = -reflected.y;
        }

        if (hit.vertical_wall != nullptr) {
            reflected.x = -reflected.x;
        }

        return reflected;
    }

    Vec2 safe_contact_position(const Vec2 &contact_point, const CollisionHit &hit, const Vec2 &velocity, float radius) {
        Vec2 position = contact_point;

        if (hit.horizontal_wall != nullptr) {
            const float direction = velocity.y >= 0.0f ? 1.0f : -1.0f;
            position.y = static_cast<float>(hit.horizontal_wall->y1) + direction * radius;
        }

        if (hit.vertical_wall != nullptr) {
            const float direction = velocity.x >= 0.0f ? 1.0f : -1.0f;
            position.x = static_cast<float>(hit.vertical_wall->x1) + direction * radius;
        }

        return position;
    }

    Vec2 apply_safe_nudge(const Vec2 &position, const CollisionHit &hit, const Vec2 &velocity, float radius, float nudge, const pong::Wall *const *walls, std::size_t wall_count) {
        if (nudge <= 0.0f) {
            return position;
        }

        Vec2 nudged = position;

        if (hit.horizontal_wall != nullptr) {
            nudged.y += (velocity.y >= 0.0f ? nudge : -nudge);
        }

        if (hit.vertical_wall != nullptr) {
            nudged.x += (velocity.x >= 0.0f ? nudge : -nudge);
        }

        if (touches_any_other_wall(nudged, radius, walls, wall_count, hit.horizontal_wall, hit.vertical_wall)) {
            return position;
        }

        return nudged;
    }
}

namespace pong {
    Game::Game(int ball_radius, int player_width, int player_height, int field_width, int field_height, int player_offset,
             float player_accel, float player_top_speed, float ball_accel) {
        ball.radius = ball_radius;
        const float raw_x = static_cast<float>((std::rand() % 200) - 100);
        const float raw_y = static_cast<float>((std::rand() % 200) - 100);
        const float raw_length = std::sqrt(raw_x * raw_x + raw_y * raw_y);
        const float normalized_x = nearly_zero(raw_length) ? 1.0f : raw_x / raw_length;
        const float normalized_y = nearly_zero(raw_length) ? 0.0f : raw_y / raw_length;
        ball.x_vel = normalized_x * ball.vel;
        ball.y_vel = normalized_y * ball.vel;

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
        move_player(player_one, p1_walls, player_one_move);
        move_player(player_two, p2_walls, player_two_move);

        Vec2 position{ball.x, ball.y};
        Vec2 velocity{ball.x_vel, ball.y_vel};
        float remaining_fraction = 1.0f;

        for (int iteration = 0; iteration < 16; ++iteration) {
            Vec2 travel = velocity * remaining_fraction;

            if (nearly_zero(travel.x) && nearly_zero(travel.y)) {
                break;
            }

            CollisionHit hit = find_closest_hit(position, travel, static_cast<float>(ball.radius), walls, 12);

            if (!hit.found) {
                position = position + travel;
                remaining_fraction = 0.0f;
                break;
            }

            position = position + travel * hit.t;
            remaining_fraction *= (1.0f - hit.t);
            velocity = reflect_velocity(velocity, hit);
            position = safe_contact_position(position, hit, velocity, static_cast<float>(ball.radius));
            position = apply_safe_nudge(position, hit, velocity, static_cast<float>(ball.radius), physics.collision_nudge, walls, 12);
        }

        ball.x = position.x;
        ball.y = position.y;
        ball.x_vel = velocity.x;
        ball.y_vel = velocity.y;


    }

    void Game::move_player(PlayerData &player,WallGroup &walls, Move move) {
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

        walls.assign_walls(0, 0, player.width, player.height);
    }
}
