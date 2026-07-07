#ifndef SHAREDVARIABLES_H_
#define SHAREDVARIABLES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int **board ;

int BWIDTH = 1020 ;
int BHEIGHT = 840 ;
int PHEIGHT = BHEIGHT - 60 ; // 780

int time_left = 180 ;
int score = 0 ;
int mode = 0 ;      //1 for Taxi Driver, 2 for Delivery Driver, 3 for Leaderboard
int fuel_left = 5000 ; //Fuel Rate 500ml for 1 buck
string player_name ;
float money ;
int jobs_completed = 0 ;
bool mode_change = true ;

const int nxcells = 1020 / 68 ; // 15 cells along x axis, 68 pixels wide (columns)
const int nycells = 780 / 52 ; // 15 cells along y axis, 52 pixel tall (rows)
int cellwidth = 68 ;
int cellheight = 52 ;

const int MAX_OCAR_SIZE = 4 ;
int CURRENT_OCAR_SIZE = 1 ;
int PASSENGER_AMOUNT = 0 ;
int DELIVERYBOX_AMOUNT = 0 ;

Mix_Chunk* CarSound = nullptr ;
Mix_Chunk* GarageSound = nullptr ;
Mix_Chunk* DoorSound = nullptr ;
Mix_Chunk* CashSound = nullptr ;
Mix_Chunk* FuelSound = nullptr ;
Mix_Chunk* BoxSound = nullptr ;
Mix_Music* bgMusic = nullptr ;
bool play_music = true ;

void Pixels2Cell(float px, float py, int& cx, int& cy) {
    cx = px / cellwidth ;
    cy = py / cellheight ;
}

void Cell2Pixels(int cx, int cy, int& px, int& py) {
    px = cx * cellwidth ;
    py = cy * cellheight ;
}

void AllocateBoardArray(int r, int c) {
    board = new int *[r] ;

    for (int i = 0 ; i < r ; i++) {
		board[i] = new int [c] ;

		for (int j = 0; j < c; j++)
			board[i][j] = 0 ;
	}       
}

#endif