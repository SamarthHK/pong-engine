//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_BALL_DATA_H
#define PONG_BALL_DATA_H

namespace pong::state_files {
    /*
     *@brief BallData struct holds the data for the ball in the game.
     */
    struct BallData {
    public:
        int radius;
        float x = 0, y = 0;
        float x_vel = 0, y_vel = 0;
        float vel = 10;
        /*
         *@brief BallData constructor initializes the ball data with default values.
         *@param radius The radius of the ball.
         *@param vel The velocity of the ball.
         */
        BallData(int radius = 5, float vel = 10):
            radius(radius),
            vel(vel)
            {};
    };
}

#endif //PONG_BALL_DATA_H
