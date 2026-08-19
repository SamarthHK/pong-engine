//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_PLAYER_DATA_H
#define PONG_PLAYER_DATA_H

namespace state_files {
    struct PlayerData {
    public:
        int width, height;
        float x = 0, y = 0, y_vel = 0;
    public:
        PlayerData(int width, int height);
    };
}



#endif //PONG_PLAYER_DATA_H
