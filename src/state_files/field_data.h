//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_FEILD_DATA_H
#define PONG_FEILD_DATA_H

namespace pong::state_files {
    struct FieldData {
    public:
        int player_offset, field_width, field_height;
        FieldData(int player_offset = 30, int field_width = 120, int field_height = 80):
            player_offset(player_offset),
            field_width(field_width),
            field_height(field_height)
            {};
    };
}

#endif //PONG_FEILD_DATA_H
