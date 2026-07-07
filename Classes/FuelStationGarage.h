#ifndef FUELSTATIONGARAGE_H_
#define FUELSTATIONGARAGE_H_

#include "../util.h"
#include "SharedVariables.h"

class FuelStation {
    int width ;
    int height ;
    int position_x ;
    int position_y ;
    int nx ;
    int ny ;
    Car *car ;

public:
    FuelStation(): width(40), height(50), car(nullptr) {
        do {
            nx = rand() % nxcells ; // generates random n from 0 to 14
            ny = rand() % nycells ;
        }
        while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;

        board[nx][ny] = -2 ;

        position_x = (nx * cellwidth) ;
        position_y = (ny * cellheight) ;
    }

    void DrawFuelStation() {
        DrawRectangle(position_x + 14, position_y + 1, 40, 50, colors[RED]) ;
        DrawRectangle(position_x + 14, position_y + height - 18, 15, 20, colors[WHITE]) ;
        DrawCircle(position_x + width, position_y + 15, 5, colors[WHITE]) ;
    }

    void FuelRefill(unsigned char key) {
        float car_x = car->getPostionX() ;
        float car_y = car->getPostionY() ;

        if ((ny + 1 < nycells && (board[nx][ny+1] == 1 && abs((position_y + height) - car_y) < 15) ||
            (ny - 1 >= 0 && board[nx][ny-1] == 1 && abs((position_y - height) - car_y) < 15) ||
            (nx + 1 < nxcells && board[nx+1][ny] == 1 && abs((position_x + width) - car_x) < 32) || 
            (nx - 1 >= 0 && board[nx-1][ny] == 1 && abs((position_x - width) - car_x) < 32)))  {
            if (key == 'f') {
                if (money > 0 && fuel_left < 5000) {
                    float refillcapacity = (5000 - fuel_left) ;
                    float refillamount = 500 * money ;

                    if (refillamount <= refillcapacity) {
                        fuel_left += refillamount ;
                        money = 0 ;
                    }
                    else {
                        float returnmoney = refillamount - refillcapacity ;
                        fuel_left += refillcapacity ;
                        returnmoney /= 500 ;
                        money = returnmoney ; 
                    }

                    Mix_PlayChannel(-1, FuelSound, 0) ; 
                }
            }
        }
    }

    void AggregateCar(Car *c) {
        car = c ;
    }
};

class Garage {
    int width ;
    int height ;
    int position_x ;
    int position_y ;
    Car *car ;

public:
    Garage(Car *c): width(45), height(50), position_x(11), position_y(1) {
        car = c ;
    }

    void DrawGarage() {
        DrawRectangle(position_x, position_y, 45, 50, colors[BLACKO]) ;
        DrawRectangle(position_x + 8, position_y + 5, 30, 10, colors[DARK_GRAY]) ;
        DrawRectangle(position_x + 8, position_y + 20, 30, 10, colors[DARK_GRAY]) ;
        DrawRectangle(position_x + 8, position_y + 35, 30, 10, colors[DARK_GRAY]) ;
    }

    void ModeChange(unsigned char key) {
        float car_x = car->getPostionX() ;
        float car_y = car->getPostionY() ;

        if ((abs((position_y + height) - car_y) < 10 && board[0][1] == 1) ||
            (abs((position_x + width) - car_x) < 20 && board[1][0] == 1)) {
            if (key == 'p') {
                if (mode == 1)
                    mode = 2 ;
                else
                    mode = 1 ;

                mode_change = true ;

                if (!Mix_Playing(-1)) {
                    Mix_PlayChannel(-1, GarageSound, 0) ;
                }
            }
        }
    }
};

#endif