#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "Board.h"
#include "Leaderboard.h"

class GameMenu{
    Board GameBoard ;
    Leaderboard leaderboard ;

public:
    bool gamestartflag ;
    bool gameendflag ;

    GameMenu(): gamestartflag(false), gameendflag(false) {}

    Board& getGameBoard() {
        return GameBoard ;
    }
    
    void displayIntroMenu() {
        glClearColor(1, 1, 1, 1) ;
        glClear (GL_COLOR_BUFFER_BIT) ;
    
        DrawString((BWIDTH / 2 - 125), (BHEIGHT/2 + 100), "1. Play as TAXI DRIVER", colors[DARK_BLUE]) ;
        DrawString((BWIDTH / 2 - 155), (BHEIGHT/2 + 25), "2. Play as DELIVERY DRIVER", colors[DARK_BLUE]) ;
        DrawString((BWIDTH / 2 - 90), (BHEIGHT/2 - 50), "3. LEADERBOARD", colors[DARK_BLUE]) ;
    
        glutPostRedisplay() ;
        glutSwapBuffers(); 
    }

    void displayPlayMenu() {
        glClearColor(1, 1, 1, 1) ;
        glClear (GL_COLOR_BUFFER_BIT) ;

        if (time_left > 15)
		    DrawString(50, BHEIGHT-30, "Time Left: " + Num2Str(time_left) + " secs", colors[NAVY]) ;
	    else
		    DrawString(50, BHEIGHT-30, "Hurry up! Time Left: " + Num2Str(time_left) + " secs", colors[RED]) ;

	    DrawString(BWIDTH / 2 - 150, BHEIGHT-30, "Score=" + Num2Str(score), colors[MAROON]) ;
        DrawString(BWIDTH / 2 + 100, BHEIGHT-30, "Money=$" + to_string(money), colors[GREEN]) ;
        DrawString(BWIDTH / 2 + 350, BHEIGHT-30, "Fuel Left=" + Num2Str(fuel_left/50),
                    colors[RED]) ;
	    DrawLine(10, BHEIGHT-45, BWIDTH-10, BHEIGHT-45, 2, colors[BLACKO]) ;

        //Display items on Screen
        GameBoard.DrawRoads() ;
        GameBoard.displayGarage() ;
        GameBoard.displayObstacles() ;
        GameBoard.displayFuelStations() ;
        GameBoard.displayPassenger() ;
        GameBoard.displayDeliveryBox() ;
        GameBoard.displayCar() ;
        // Mode change
        if (mode_change) {
            GameBoard.GeneratePlayables() ;
            mode_change = false ;
        }

        if (fuel_left == 0 || time_left <= 0) {
            gamestartflag = false ;
            gameendflag = true ;
            leaderboard.SaveHighScores() ;
            time_left = -1 ;
        }

        glutPostRedisplay() ;
        glutSwapBuffers(); 
    }

    void displayEndMenu() {
        glClearColor(1, 1, 1, 1) ;
        glClear (GL_COLOR_BUFFER_BIT) ;
    
        if (score >= 100) {
            DrawString(435, BHEIGHT/2 + 100, "You won champ!", colors[RED]) ;
            DrawString(440, BHEIGHT/2 + 25, "Your score: " + Num2Str(score), colors[DARK_BLUE]) ;
        }
        else if (fuel_left == 0) {
            DrawString(415, BHEIGHT/2 + 100, "You ran out of fuel!", colors[RED]) ;
            DrawString(440, BHEIGHT/2 + 25, "Your score: " + Num2Str(score), colors[DARK_BLUE]) ;
        }
        else {
            DrawString(300, BHEIGHT/2 + 100, "You ran out of time! Better luck next time ;)", colors[RED]) ;
            DrawString(440, BHEIGHT/2 + 25, "Your score: " + Num2Str(score), colors[DARK_BLUE]) ;
        }
    
        glutPostRedisplay() ;
        glutSwapBuffers(); 
    }

    void displayLeaderBoard() {
        glClearColor(1, 1, 1, 1) ;
        glClear (GL_COLOR_BUFFER_BIT) ;

        leaderboard.DisplayHighScores() ;

        DrawString((BWIDTH / 2 - 135), 200, "Press 1 or 2 to start playing as", colors[DARK_BLUE]) ;
        DrawString((BWIDTH / 2 - 75), 150, "1. TAXI DRIVER", colors[BLUE]) ;
        DrawString((BWIDTH / 2 - 105), 100, "2. DELIVERY DRIVER", colors[BLUE]) ;

        glutPostRedisplay() ;
        glutSwapBuffers(); 
    }
};

#endif