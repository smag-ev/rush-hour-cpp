#ifndef PASSENGERDELIVERYBOX_H_
#define PASSENGERDELIVERYBOX_H_

#include "../util.h"
#include "SharedVariables.h"

class Passenger {
protected:
    int width ;
    int height ;
    int position_x ;
    int position_y ;
    int dposition_x ;
    int dposition_y ;
    bool this_picked_up ;
    int nx ;
    int ny ;
    int dnx ;
    int dny ;
    int orders_completed ;
    Car *car ;

public:
    static bool picked_up ;

    Passenger(): width(32), height(50), orders_completed(0), car(nullptr), this_picked_up(false) {
        do {
            nx = rand() % nxcells ; // generates random n from 0 to 14
            ny = rand() % nycells ;
        }
        while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;

        board[nx][ny] = -3 ;
    }

    void DrawPassenger() {
        position_x = (nx * cellwidth) ;
        position_y = (ny * cellheight) ;

        if (board[nx][ny] == -3 && mode == 1) {
            DrawCircle(position_x + 34, position_y + 39, 12, colors[BLACK]) ;
            DrawLine(position_x + 34, position_y + 27, position_x + 18, position_y + 17, 6, colors[BLACK]) ;
            DrawLine(position_x + 34, position_y + 27, position_x + 50, position_y + 17, 6, colors[BLACK]) ;
            DrawLine(position_x + 34, position_y + 27, position_x + 34, position_y + 17, 6, colors[BLACK]) ;
            DrawLine(position_x + 34, position_y + 17, position_x + 18, position_y + 1, 6, colors[BLACK]) ;
            DrawLine(position_x + 34, position_y + 17, position_x + 50, position_y + 1, 6, colors[BLACK]) ;
        }

        dposition_x = (dnx * cellwidth) ;
        dposition_y = (dny * cellheight) ;

        if (mode == 1 && this_picked_up) {
            DrawRectangle(dposition_x, dposition_y, cellwidth, cellheight, colors[LIGHT_GREEN]) ;
        }
    }

    void PickupNDrop(unsigned char key) {
        float car_x = car->getPostionX() ;
        float car_y = car->getPostionY() ;

        int car_nx, car_ny ;

        Pixels2Cell(car_x, car_y, car_nx, car_ny) ;

        if (mode == 1 && !picked_up) {
            if ((ny + 1 < nycells && (board[nx][ny+1] == 1 && abs((position_y + height) - car_y) < 15) ||
                (ny - 1 >= 0 && board[nx][ny-1] == 1 && abs((position_y - height) - car_y) < 15) ||
                (nx + 1 < nxcells && board[nx+1][ny] == 1 && abs((position_x + width) - car_x) < 40) || 
                (nx - 1 >= 0 && board[nx-1][ny] == 1 && abs((position_x - width) - car_x) < 40))) {
                if (key == ' ') {
                    picked_up = true ;
                    this_picked_up = true ;
                    board[nx][ny] = 0 ;
                    GenerateDestination() ;

                    Mix_PlayChannel(-1, DoorSound, 0) ; 
                }
            }
        }

        if (mode == 1 && this_picked_up) {
            if ((abs(car_nx - dnx) < 1 && abs(car_ny - dny) < 1)) {
                if (key == ' ') {
                    picked_up = false ;
                    this_picked_up = false ;
                    board[dnx][dny] = 0 ;
                    score += 10 ;
                    money += 2 ;

                    jobs_completed++ ;

                    do {
                        nx = rand() % nxcells ;
                        ny = rand() % nycells ;
                    }
                    while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;
            
                    board[nx][ny] = -3 ;

                    Mix_PlayChannel(-1, CashSound, 0) ; 
                }
            }
        }
    }

    void GenerateDestination() {
        if (this_picked_up) {
            do {
                dnx = rand() % nxcells ; // generates random n from 0 to 14
                dny = rand() % nycells ;
            }
            while (board[dnx][dny] <= -1 || board[dnx][dny] == 1) ;
    
            board[dnx][dny] = -10 ;
        }
    }

    void AggregateCar(Car *c) {
        car = c ;
    }
};

bool Passenger::picked_up = false ;

class DeliveryBox: public Passenger {

public:
    DeliveryBox() {
        width = 40 ;
        height = 40 ;

        do {
            nx = rand() % nxcells ; // generates random n from 0 to 14
            ny = rand() % nycells ;
        }
        while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;

        board[nx][ny] = -4 ;
    }

    void DrawDeliveryBox() {
        position_x = (nx * cellwidth) ;
        position_y = (ny * cellheight) ;

        if (board[nx][ny] == -4 && mode == 2) {
            DrawSquare(position_x + 14, position_y + 6, 40, colors[ROSY_BROWN]) ;
            DrawRectangle(position_x + 26, position_y + height, 16, 11, colors[CORAL]) ;
        }

        dposition_x = (dnx * cellwidth) ;
        dposition_y = (dny * cellheight) ;

        if (mode == 2 && this_picked_up)
            DrawRectangle(dposition_x, dposition_y, cellwidth, cellheight, colors[LIGHT_GREEN]) ;
    }

    void PickupNDrop(unsigned char key) {
        float car_x = car->getPostionX() ;
        float car_y = car->getPostionY() ;

        int car_nx, car_ny ;

        Pixels2Cell(car_x, car_y, car_nx, car_ny) ;

        if (mode == 2 && !picked_up) {
            if ((ny + 1 < nycells && (board[nx][ny+1] == 1 && abs((position_y + height) - car_y) < 15) ||
                (ny - 1 >= 0 && board[nx][ny-1] == 1 && abs((position_y - height) - car_y) < 15) ||
                (nx + 1 < nxcells && board[nx+1][ny] == 1 && abs((position_x + width) - car_x) < 40) || 
                (nx - 1 >= 0 && board[nx-1][ny] == 1 && abs((position_x - width) - car_x) < 40))) {
                if (key == ' ') {
                    picked_up = true ;
                    this_picked_up = true ;
                    board[nx][ny] = 0 ;
                    GenerateDestination() ;

                    Mix_PlayChannel(-1, BoxSound, 0) ; 
                }
            }
        }

        if (mode == 2 && this_picked_up) {
            if ((abs(car_nx - dnx) < 1 && abs(car_ny - dny) < 1)) {
                if (key == ' ') {
                    picked_up = false ;
                    this_picked_up = false ;
                    board[dnx][dny] = 0 ;
                    score += 20 ;
                    money += 3 ;

                    jobs_completed++ ;

                    do {
                        nx = rand() % nxcells ;
                        ny = rand() % nycells ;
                    }
                    while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;
            
                    board[nx][ny] = -4 ;

                    Mix_PlayChannel(-1, CashSound, 0) ; 
                }
            }
        }
    }

    void GenerateDestination() {
        if (this_picked_up) {
            do {
                dnx = rand() % nxcells ; // generates random n from 0 to 14
                dny = rand() % nycells ;
            }
            while (board[dnx][dny] <= -1 || board[dnx][dny] == 1) ;
    
            board[dnx][dny] = -10 ;
        }
    }
};

#endif