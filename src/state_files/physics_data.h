//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_PHYSICS_DATA_H
#define PONG_PHYSICS_DATA_H

namespace pong::state_files {
    /*
     *@brief PhysicsData struct holds the data for the physics in the game.
     */
    struct PhysicsData {
    public:
        float player_accel, player_top_speed, ball_accel, player_friction;
        /*
         *@brief PhysicsData constructor initializes the physics data with default values.
         *@param player_accel The acceleration of the player.
         *@param player_top_speed The top speed of the player.
         *@param ball_accel The acceleration of the ball after each hit.
         */
        PhysicsData(float player_accel = 3, float player_top_speed = 10, float ball_accel = 1.05):
            player_accel(player_accel),
            player_top_speed(player_top_speed),
            ball_accel(ball_accel)
            {
                player_friction = player_top_speed / (player_top_speed + ball_accel);
            };
    };
}

#endif //PONG_PHYSICS_DATA_H
