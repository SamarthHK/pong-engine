//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_FEILD_DATA_H
#define PONG_FEILD_DATA_H

namespace pong::state_files {
    /*
     *@brief FieldData struct holds the data for the field in the game.
     */
    struct FieldData {
    public:
        int player_offset, field_width, field_height;
        /*
         *@brief FieldData constructor initializes the field data with default values.
         *@param player_offset The offset of the player from the edge of the field.
         *@param field_width The width of the field.
         *@param field_height The height of the field.
         */
        FieldData(int player_offset = 30, int field_width = 120, int field_height = 80):
            player_offset(player_offset),
            field_width(field_width),
            field_height(field_height)
            {};
    };
}

#endif //PONG_FEILD_DATA_H
