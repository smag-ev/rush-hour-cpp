#ifndef OBSTACLES_H_
#define OBSTACLES_H_

#include "../util.h"
#include "SharedVariables.h"

//IMPORTANT NOTES FOR ME
// -1 at buildings position
// -1 at trees position
// -2 at fuel stations position
// -3 at passenger position
// -4 at delivery box postion
// -5 at garage position
// -10 at destination position
// -6, -7, -8, -9 at obstacle car position

struct Buildings {
    int width ;
    int height ;
    int position_x ;
    int position_y ;

    void display() {
        DrawRectangle(position_x, position_y, width, height, colors[BLACK]);
        DrawRectangle(position_x + 19, (position_y + height/2) - 8, 30, 16, colors[CYAN]);
        DrawRectangle((position_x + width/2) - 15, (position_y + height/2) - 8, 30, 16, colors[CYAN]);
        DrawRectangle((position_x + width) - 49, (position_y + height/2) - 8, 30, 16, colors[CYAN]);
    }
};

class Trees {
    int width ;
    int height ;
    int position_x ;
    int position_y ;

public:
    Trees(): width(35), height(50) {
        int nx ;
        int ny ;

        do {
            nx = rand() % nxcells ; // generates random n from 0 to 14
            ny = rand() % nycells ;
        }
        while (board[nx][ny] <= -1 || board[nx][ny] == 1) ;

        board[nx][ny] = -1 ;

        position_x = (nx * cellwidth) ;
        position_y = (ny * cellheight) ;
    }

    void display() {
        DrawRectangle(position_x + 26, position_y, 15, 20, colors[SADDLE_BROWN]) ;
        DrawRectangle(position_x + 16, position_y + 20, 35, 30, colors[GREEN]) ;
    }
};

class OCar {
    int width ;
    int height ;
    float position_x ;
    float position_y ;
    static int p_assigner ;
    int uid ;
    int direction ;

public:
    static float speed ;

    OCar(): width(45), height(50) {
        int nx ;
        int ny ;

        do {
            nx = rand() % nxcells ; // generates random n from 0 to 14
            ny = rand() % nycells ;
        }
        while (board[nx][ny] <= -1  || board[nx][ny] == 1) ;

        direction = rand() % 4 ;

        p_assigner-- ;
        uid = p_assigner ;

        board[nx][ny] = p_assigner ;

        position_x = (nx * cellwidth) ;
        position_y = (ny * cellheight) ;
    }

    void display() {
        DrawCircle(position_x + 8, position_y + 8, 7, colors[BLACK]) ;
        DrawCircle(position_x + 37, position_y + 8, 7, colors[BLACK]) ;
        DrawRectangle(position_x + 1, position_y + 8, 45, 43, colors[RED]) ;
        DrawRectangle(position_x + 1, position_y + 35, 45, 16, colors[DEEP_PINK]) ;
        DrawRectangle(position_x + 6, position_y + 19, 13, 7, colors[WHITE]) ;
        DrawRectangle(position_x + 28, position_y + 19, 13, 7, colors[WHITE]) ;
    }

    void RandomMovement() {
        int old_nx, old_ny ;
        Pixels2Cell(position_x, position_y, old_nx, old_ny) ;

        bool movement = true ;
    
        float new_x = position_x ;
        float new_y = position_y ;
        
        switch(direction) {
            case 0:
                new_y += speed ; break ;
            case 1:
                new_y -= speed ; break ;
            case 2:
                new_x += speed ; break ;
            case 3:
                new_x -= speed ; break ;
        }
    
        if (new_x < 0 || new_y < 0 || new_x + width >= BWIDTH || new_y + height >= PHEIGHT)
            movement = false ;

        else {
            int check_nx1, check_ny1 ;
            int check_nx2, check_ny2 ;
        
            if (direction == 0) {
                Pixels2Cell(new_x, new_y + height, check_nx1, check_ny1) ;
                Pixels2Cell(new_x + width, new_y + height, check_nx2, check_ny2) ;
            }
            else if (direction == 1) {
                Pixels2Cell(new_x, new_y, check_nx1, check_ny1) ;
                Pixels2Cell(new_x + width, new_y, check_nx2, check_ny2) ;
            }
            else if (direction == 2) {
                Pixels2Cell(new_x + width, new_y, check_nx1, check_ny1) ;
                Pixels2Cell(new_x + width, new_y + height, check_nx2, check_ny2) ;
            }
            else if (direction == 3) {
                Pixels2Cell(new_x, new_y, check_nx1, check_ny1) ;
                Pixels2Cell(new_x, new_y + height, check_nx2, check_ny2) ;
            }
    
            if ((board[check_nx1][check_ny1] <= -1 && board[check_nx1][check_ny1] != uid) || 
                (board[check_nx2][check_ny2] <= -1 && board[check_nx2][check_ny2] != uid) ||
                (board[check_nx1][check_ny1] == 1 || board[check_nx2][check_ny2] == 1)) {
                movement = false ;
            }
        }
    
        if (movement) {
            position_x = new_x ;
            position_y = new_y ;
        }
        else
            direction = rand() % 4 ;
    
        board[old_nx][old_ny] = 0 ;

        int new_nx, new_ny ;
        Pixels2Cell(position_x, position_y, new_nx, new_ny) ;

        if (board[new_nx][new_ny] == 0 || board[new_nx][new_ny] == uid)
            board[new_nx][new_ny] = uid ;
    }
};

int OCar::p_assigner = -6 ;
float OCar::speed = 0.25 ;

class Obstacles {
    Buildings *buildings ;
    Trees *trees ;
    OCar *ocar ;

public:
    Obstacles() {
        srand(time(0)) ;

        AllocateBoardArray(nxcells, nycells) ;
        board[0][14] = 1 ; //For car
        board[0][0] = -5 ; //For Garage

        buildings = new Buildings[9] ;

        buildings[0] = {68*3, 52*1, 68*2, PHEIGHT - 52*3} ;
        board[2][12] = -1 ;
        board[3][12] = -1 ;
        board[4][12] = -1 ;

        buildings[1] = {68*3, 52*3, 68*2, PHEIGHT - 52*9} ;
        board[2][6] = -1 ;  board[2][7] = -1 ;
        board[3][6] = -1 ;  board[2][8] = -1 ;
        board[4][6] = -1 ;  board[3][7] = - 1 ;
        board[3][8] = -1 ;  board[4][7] = -1 ;
        board[4][8] = -1 ;

        buildings[2] = {68*3, 52*1, 68*6, PHEIGHT - 52*8} ;
        board[6][7] = -1 ;
        board[7][7] = -1 ;
        board[8][7] = -1 ;

        buildings[3] = {68*1, 52*6, 68*8, PHEIGHT - 52*8} ;
                            board[8][10] = -1 ;
        board[8][8] = -1 ;  board[8][11] = -1 ;
        board[8][9] = -1 ;  board[8][12] = -1 ;

        buildings[4] = {68*4, 52*1, 68*11, PHEIGHT - 52*2} ;
        board[11][13] = -1 ;
        board[12][13] = -1 ;
        board[13][13] = -1 ;
        board[14][13] = -1 ;

        buildings[5] = {68*1, 52*4, 68*10, PHEIGHT - 52*13} ;
        board[10][2] = -1 ;
        board[10][3] = -1 ;
        board[10][4] = -1 ;
        board[10][5] = -1 ;

        buildings[6] = {68*4, 52*1, 68*10, PHEIGHT - 52*13} ;
        board[11][2] = -1 ;
        board[12][2] = -1 ;
        board[13][2] = -1 ;

        buildings[7] = {68*6, 52*1, 68*1, PHEIGHT - 52*12} ;
        board[1][3] = -1 ;  board[2][3] = -1 ;
        board[3][3] = -1 ;  board[4][3] = -1 ;
        board[5][3] = -1 ;  board[6][3] = -1 ;

        buildings[8] = {68*1, 52*5, 68*12, PHEIGHT - 52*9} ;
        board[12][6] = -1 ; board[12][7] = -1 ;
        board[12][8] = -1 ; board[12][9] = -1 ;
        board[12][10] = -1 ;

        trees = new Trees[5] ;

        ocar = new OCar[CURRENT_OCAR_SIZE] ;
    }

    ~Obstacles() {
        delete[] buildings ;
        delete[] trees ;
        delete[] ocar ;
    }

    Buildings* getBuildings() {
        return buildings ;
    }
    Trees* getTrees() {
        return trees ;
    }
    OCar* getObstacleCars() {
        return ocar ;
    }

    void DrawBuildings() {
        for (int i = 0 ; i < 9 ; i++) {
            buildings[i].display() ;
        }
    }

    void DrawTrees() {
        for (int i = 0 ; i < 5 ; i++)
            trees[i].display() ;
    }

    void DrawObstacleCars() {
        for (int i = 0 ; i < CURRENT_OCAR_SIZE ; i++) {
            ocar[i].display() ;
            ocar[i].RandomMovement() ;
        }
    }

    void GenerateObstacleCars() {
        if (jobs_completed % 2 == 0 && jobs_completed != 0 && jobs_completed <= 6) {

            static int last_job_checked = 0 ;
    
            if (last_job_checked == jobs_completed)
                return ;

            last_job_checked = jobs_completed ;

            OCar::speed *= 2 ;
    
            if (CURRENT_OCAR_SIZE < MAX_OCAR_SIZE) {
                CURRENT_OCAR_SIZE++ ;
    
                OCar* new_ocar = new OCar[CURRENT_OCAR_SIZE] ;
    
                for (int i = 0; i < CURRENT_OCAR_SIZE - 1; i++)
                    new_ocar[i] = ocar[i];
    
                new_ocar[CURRENT_OCAR_SIZE - 1] = OCar() ;
    
                delete[] ocar ;

                ocar = new_ocar ;
            }
        }
    }
};

#endif