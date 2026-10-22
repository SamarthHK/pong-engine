//
// Created by munna-01 on 8/19/26.
//

#ifndef PONG_WALL_H
#define PONG_WALL_H

namespace pong::state_files {
    /*
     *@brief WallOrientation enum defines the orientation of a wall.
     */
    enum class WallOrientation {
        Horizontal,
        Vertical
    };
    /*
     *@brief Wall struct holds the data for a wall in the game.
     */
    struct Wall {
        int x1,y1,x2,y2;
        WallOrientation orientation = WallOrientation::Horizontal;
        /*
         *@brief Wall constructor initializes the wall data with default values, and when assigning a wall orientation should be bottom left to top right.
         *@param x1 The x coordinate of the first point of the wall.
         *@param y1 The y coordinate of the first point of the wall.
         *@param x2 The x coordinate of the second point of the wall.
         *@param y2 The y coordinate of the second point of the wall.
         *@param orientation The orientation of the wall.
         */
        Wall(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, WallOrientation orientation = WallOrientation::Horizontal)
            : x1(x1), y1(y1), x2(x2), y2(y2), orientation(orientation) {
        }
    };
    /*
     *@brief Box struct holds the data for a box in the game.
     */
    struct Box{
    public:
        Wall left_wall;
        Wall right_wall;
        Wall top_wall;
        Wall bottom_wall;
        Box() : left_wall(), right_wall(), top_wall(), bottom_wall() {};

        Box(float x1, float y1, float width_x2, float height_y2, bool centered = true) {
            Box();
            assign_box_walls(x1, y1, width_x2, height_y2, centered);
        }

        void assign_box_walls(float x1, float y1, float width_x2, float height_y2, bool centered = true) {
            if (centered) {
                assign_horizontal_wall(&top_wall, y1+height_y2/2,x1-width_x2/2, x1+width_x2/2);
                assign_horizontal_wall(&bottom_wall, y1-height_y2/2, x1-width_x2/2, x1+width_x2/2);
                assign_vertical_wall(&left_wall, x1-width_x2/2, y1-height_y2/2, y1+height_y2/2);
                assign_vertical_wall(&right_wall, x1+width_x2/2, y1-height_y2/2, y1+height_y2/2);
                return;
            }
            assign_horizontal_wall(&top_wall, height_y2,x1, width_x2);
            assign_horizontal_wall(&bottom_wall, y1, x1, width_x2);
            assign_vertical_wall(&left_wall, x1, y1, height_y2);
            assign_vertical_wall(&right_wall, width_x2, y1, height_y2);
        }

    private:
        static void assign_horizontal_wall(Wall *wall, float y, float x1, float x2) {
            wall->y1 = wall->y2 = y;
            wall->x1 = x1;
            wall->x2 = x2;
            wall->orientation = WallOrientation::Horizontal;
        }

        static void assign_vertical_wall(Wall *wall, float x, float y1, float y2) {
            wall->x1 = wall->x2 = x;
            wall->y1 = y1;
            wall->y2 = y2;
            wall->orientation = WallOrientation::Vertical;
        }
    };
}

#endif //PONG_WALL_H
