//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_WALL_H
#define PONG_WALL_H

namespace pong {
    struct Wall {
        int x1,y1,x2,y2;
        Wall(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : x1(x1), y1(y1), x2(x2), y2(y2) {
        }
    };
    struct WallGroup{
        Wall left_wall;
        Wall right_wall;
        Wall top_wall;
        Wall bottom_wall;
        WallGroup() : left_wall(), right_wall(), top_wall(), bottom_wall() {}

        void assign_walls(float x, float y, float width, float height) {
            assign_horizontal_wall(&top_wall, y+height/2,x-width/2, x+width/2);
            assign_horizontal_wall(&bottom_wall, y-height/2, x-width/2, x+width/2);
            assign_vertical_wall(&left_wall, x-width/2, y-height/2, y+height/2);
            assign_vertical_wall(&right_wall, x+width/2, y-height/2, y+height/2);
        }

        void assign_horizontal_wall(Wall *wall, float y, float x1, float x2) {
            wall->y1 = wall->y2 = y;
            wall->x1 = x1;
            wall->x2 = x2;
        }

        void assign_vertical_wall(Wall *wall, float x, float y1, float y2) {
            wall->x1 = wall->x2 = x;
            wall->y1 = y1;
            wall->y2 = y2;
        }
    };
}

#endif //PONG_WALL_H
