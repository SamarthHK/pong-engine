//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_BALL_DATA_H
#define PONG_BALL_DATA_H

namespace pong::state_files {
    struct BallData {
    public:
        int radius, x = 0, y = 0;
        float angle = 0, vel = 10;
        BallData(int radius = 5):
            radius(radius)
            {};
    };
}

#endif //PONG_BALL_DATA_H
