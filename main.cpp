//============================================================================
// Name        : .cpp
// Author      : Dr. Sibt Ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include "GameClasses/GameMenu.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;


// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

GameMenu game_menu ;

void GameDisplay()/**/{
	if (!game_menu.gamestartflag && mode == 0) {

		game_menu.displayIntroMenu() ;
			
	//Game Still hasn't started
	}
	else if(!game_menu.gamestartflag && mode == 3) {

		game_menu.displayLeaderBoard() ;
	}
	else {
		if (play_music) {
			Mix_PlayMusic(bgMusic, -1) ;

			play_music = false ;
		}

		if (time_left >= 0) {
		
		game_menu.displayPlayMenu() ;

		// Game is still in play
		}
		else {
			game_menu.displayEndMenu() ;
		}
	}
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (game_menu.gamestartflag) {
		for (int i = 0 ; i < 5 ; i++) {
			game_menu.getGameBoard().getCar().MoveCar(key) ;

			if (i == 0) {
				if (!Mix_Playing(-1))
					Mix_PlayChannel(-1, CarSound, 0) ;
			}
		}
	}
	
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		
	} 
		else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
				
	} 
		else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		
	}
		else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	game_menu.getGameBoard().getGarage().ModeChange(key) ;

	if (game_menu.getGameBoard().getPassenger() != nullptr) {
		for (int i = 0 ; i < PASSENGER_AMOUNT ; i++)
			game_menu.getGameBoard().getPassenger()[i].PickupNDrop(key) ;
	}

	if (game_menu.getGameBoard().getDeliveryBox() != nullptr) {
		for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++)
			game_menu.getGameBoard().getDeliveryBox()[i].PickupNDrop(key) ;
	}

	for (int i = 0 ; i < DELIVERYBOX_AMOUNT ; i++) 
		game_menu.getGameBoard().getFuelStation()[i].FuelRefill(key) ;

	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == '1' && !game_menu.gamestartflag && !game_menu.gameendflag) {
		cout << "Enter your name: " ;
		getline(cin, player_name) ;
		mode = 1 ;
		game_menu.gamestartflag = true ;
	}
	if (key == '2' && !game_menu.gamestartflag && !game_menu.gameendflag) {
		cout << "Enter your name: " ;
		getline(cin, player_name) ;
		mode = 2 ;
		game_menu.gamestartflag = true ;
	}
	if (key == '3' && !game_menu.gamestartflag && !game_menu.gameendflag) {
		mode = 3 ;
	}
	
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	if (time_left > 0 && game_menu.gamestartflag)
		--time_left ;

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{

	}
		else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	SDL_Init(SDL_INIT_AUDIO) ;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;

	bgMusic = Mix_LoadMUS("Sounds/bgmusic.mp3") ;
	CarSound = Mix_LoadWAV("Sounds/carsound.wav") ;
	DoorSound = Mix_LoadWAV("Sounds/doorsound.wav") ;
	CashSound = Mix_LoadWAV("Sounds/cashsound.wav") ;
	FuelSound = Mix_LoadWAV("Sounds/fuelsound.wav") ;
	BoxSound = Mix_LoadWAV("Sounds/boxsound.wav") ;
	GarageSound = Mix_LoadWAV("Sounds/garagesound.wav") ;

	Mix_VolumeChunk(CarSound, MIX_MAX_VOLUME / 2) ;
	Mix_VolumeChunk(BoxSound, MIX_MAX_VOLUME / 2) ;

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(1060, 320); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	Mix_FreeMusic(bgMusic) ;
	Mix_CloseAudio() ;
	SDL_Quit() ;

	return 1;
}
#endif /* RushHour_CPP_ */