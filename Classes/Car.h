#ifndef CAR_H_
#define CAR_H_

#include "../util.h"
#include "SharedVariables.h"

class FuelStation ;

class Car {
    int width ;
    int height ;
    float speed ;
    float position_x ;
    float position_y ;

public:
    Car(): width(45), height(50), position_x(0), position_y(728), speed(1.1) {}

    void DrawCar() {
        if (mode == 1) {
            DrawCircle(position_x + 8, position_y + 8, 7, colors[BLACK]) ;
            DrawCircle(position_x + 37, position_y + 8, 7, colors[BLACK]) ;
            DrawRectangle(position_x + 1, position_y + 8, 45, 43, colors[ORANGE]) ;
            DrawRectangle(position_x + 1, position_y + 29, 45, 21, colors[BLACK]) ;
            DrawRectangle(position_x + 8, position_y + 36, 30, 8, colors[SKY_BLUE]) ;
            DrawRectangle(position_x + 6, position_y + 16, 13, 7, colors[WHITE]) ;
            DrawRectangle(position_x + 28, position_y + 16, 13, 7, colors[WHITE]) ;
        }
        else {
            DrawCircle(position_x + 8, position_y + 8, 7, colors[BLACK]) ;
            DrawCircle(position_x + 37, position_y + 8, 7, colors[BLACK]) ;
            DrawRectangle(position_x + 1, position_y + 8, 45, 43, colors[BLUE_VIOLET]) ;
            DrawRectangle(position_x + 1, position_y + 29, 45, 21, colors[BLUE]) ;
            DrawRectangle(position_x + 8, position_y + 36, 30, 8, colors[CYAN]) ;
            DrawRectangle(position_x + 6, position_y + 16, 13, 7, colors[WHITE]) ;
            DrawRectangle(position_x + 28, position_y + 16, 13, 7, colors[WHITE]) ;
        }
    }

    void MoveCar(int key) {
        int old_nx, old_ny ;
        Pixels2Cell(position_x, position_y, old_nx, old_ny) ;

        float new_x = position_x ;
        float new_y = position_y ;

        int check_nx1, check_nx2 ;
        int check_ny1, check_ny2 ;
        
        if (key == GLUT_KEY_UP) {
            new_y += speed ;
            Pixels2Cell(new_x, new_y + height, check_nx1, check_ny1) ;
            Pixels2Cell(new_x + width, new_y + height, check_nx2, check_ny2) ;
        }
        else if (key == GLUT_KEY_DOWN) {
            new_y -= speed ;
            Pixels2Cell(new_x, new_y, check_nx1, check_ny1) ;
            Pixels2Cell(new_x + width, new_y, check_nx2, check_ny2) ;
        }
        else if (key == GLUT_KEY_RIGHT) {
            new_x += speed ;
            Pixels2Cell(new_x + width, new_y, check_nx1, check_ny1) ;
            Pixels2Cell(new_x + width, new_y + height, check_nx2, check_ny2) ;
        }
        else if (key == GLUT_KEY_LEFT) {
            new_x -= speed ;
            Pixels2Cell(new_x, new_y, check_nx1, check_ny1) ;
            Pixels2Cell(new_x, new_y + height, check_nx2, check_ny2) ;
        }
    
        if (new_x < 0 || new_y < 0 || new_x + width >= BWIDTH || new_y + height >= PHEIGHT)
            return ;
        
        if ((board[check_nx1][check_ny1] <= -1 && board[check_nx1][check_ny1] >= -9) ||
            (board[check_nx2][check_ny2] <= -1 && board[check_nx2][check_ny2] >= -9)) {
            return ;
        }

        board[old_nx][old_ny] = 0 ; //Clear old position
    
        position_x = new_x ;
        position_y = new_y ;

        int new_nx, new_ny ;
        Pixels2Cell(position_x, position_y, new_nx, new_ny) ;
        board[new_nx][new_ny] = 1 ; //Update new position

        if (fuel_left > 0)
            fuel_left -= 1 ;
    }

    int getPostionX() {
        return position_x ;
    }
    int getPostionY() {
        return position_y ;
    }
    void setPositionX(int s) {
        position_x = s ;
    }
    void setPositionY(int s) {
        position_y = s ;
    }
};

#endif