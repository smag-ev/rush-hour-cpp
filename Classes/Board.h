#ifndef BOARD_H_
#define BOARD_H_

#include "../util.h"
#include "SharedVariables.h"
#include "Car.h"
#include "Obstacles.h"
#include "FuelStationGarage.h"
#include "PassengerDeliveyBox.h"

class Board {
    Car car ;
    Garage garage ;
    Obstacles obstacle ;
    FuelStation *fuelstation ;
    Passenger *passenger ;
    DeliveryBox *box ;

public:
    Board(): garage(&car), passenger(nullptr), box(nullptr) {
        srand(time(0)) ;

        PASSENGER_AMOUNT = rand() % 3 + 2 ;
        DELIVERYBOX_AMOUNT = rand() % 2 + 2 ;

        fuelstation = new FuelStation[DELIVERYBOX_AMOUNT] ;
        for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++)
            fuelstation[i].AggregateCar(&car) ;

        GeneratePlayables() ;
    }

    void GeneratePlayables() {
        for (int i = 0 ; i < nxcells ; i++) {
            for (int j = 0 ; j < nycells ; j++) {
                if (board[i][j] == -3 || board[i][j] == -4 || board[i][j] == -10)
                    board[i][j] = 0 ;
            }
        }

        Passenger::picked_up = false ;

        if (mode == 1) {
            if (box != nullptr) {
                delete[] box ;
                box = nullptr ;
            }

            if (passenger != nullptr) {
                delete[] passenger ;
                passenger = nullptr ;
            }

            passenger = new Passenger[PASSENGER_AMOUNT] ;
            for (int i = 0 ; i < PASSENGER_AMOUNT ; i++)
                passenger[i].AggregateCar(&car) ;
        }

        else if (mode == 2) {
            if (passenger != nullptr) {
                delete[] passenger ;
                passenger = nullptr ;
            }

            if (box != nullptr) {
                delete[] box ;
                box = nullptr ;
            }

            box = new DeliveryBox[DELIVERYBOX_AMOUNT] ;
            for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++)
                box[i].AggregateCar(&car) ;
        }
    }


    ~Board() {
        delete[] fuelstation ;
        delete[] passenger ;
        delete[] box ;
    }

    void DrawRoads() {
        int x = 0 ;

        for (int i = 0 ; i < nxcells ; i++) {
            DrawRectangle(x, 0, 68, 780, colors[GRAY]) ;
            x += 68 ;
        }
    }

    void displayCar() {
        car.DrawCar() ;
    }

    void displayGarage() {
        garage.DrawGarage() ;
    }

    void displayObstacles() {
        obstacle.DrawBuildings() ;
        obstacle.DrawTrees() ;
        obstacle.DrawObstacleCars() ;
        obstacle.GenerateObstacleCars() ;
    }

    void displayFuelStations() {
        for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++)
            fuelstation[i].DrawFuelStation() ;
    }

    void displayPassenger() {
        if (mode == 1 && passenger != nullptr) {
            for (int i = 0 ; i < PASSENGER_AMOUNT ; i++)
                passenger[i].DrawPassenger() ;
        }
    }

    void displayDeliveryBox() {
        if (mode == 2 && box != nullptr) {
            for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++)
                box[i].DrawDeliveryBox() ;
        }
    }

    Car& getCar() {
        return car ;
    }
    FuelStation* getFuelStation() {
        return fuelstation ;
    }
    Garage& getGarage() {
        return garage ;
    }
    Passenger* getPassenger() {
        return passenger ;
    }
    DeliveryBox* getDeliveryBox() {
        return box ;
    }
};  

#endif