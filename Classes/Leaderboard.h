#ifndef LEADERBOARD_H_
#define LEADERBOARD_H_

#include "fstream"
#include "../util.h"
#include "SharedVariables.h"

class Leaderboard {
public:
    void SaveHighScores() {
        string names[10] ;
        int scores[10] ;

        for (int i = 0 ; i < 10 ; i++) {
            names[i] = "" ;
            scores[i] = 0 ;
        }

        ifstream myFile("highscores.bin", ios::binary) ;

        if (myFile.is_open()) {
            for (int i = 0 ; i < 10 && !myFile.eof() ; i++) {
                int length ;

                myFile.read((char*)&length, sizeof(length)) ;

                if (myFile.eof())
                    break ;

                char* temp = new char[length + 1] ;

                myFile.read(temp, length) ;

                temp[length] = '\0' ;
                names[i] = temp ;
                delete[] temp ;

                myFile.read((char*)&scores[i], sizeof(scores[i])) ;
            }
            myFile.close() ;
        }

        int min_index = 0 ;

        for (int i = 1 ; i < 10 ; i++) {
            if (scores[i] < scores[min_index])
                min_index = i ;
        }

        if (score > scores[min_index]) {
            names[min_index] = player_name ;
            scores[min_index] = score ;

            // Sort descendingly
            for (int i = 0 ; i < 10 - 1 ; i++) {
                for (int j = i + 1 ; j < 10 ; j++) {
                    if (scores[j] > scores[i]) {
                        int temp_score = scores[i] ;
                        scores[i] = scores[j] ;
                        scores[j] = temp_score ;

                        string temp_name = names[i] ;
                        names[i] = names[j] ;
                        names[j] = temp_name ;
                    }
                }
            }

            ofstream out("highscores.bin", ios::binary) ;

            if (out.is_open()) {

                for (int i = 0; i < 10; i++) {
                    int length = names[i].size() ;

                    out.write((char*)&length, sizeof(length)) ;
                    out.write(names[i].c_str(), length) ;
                    out.write((char*)&scores[i], sizeof(scores[i])) ;
                }
                out.close();
            }
        }
    }

    void DisplayHighScores() {
        string names[10] ;
        int scores[10] ;

        for (int i = 0 ; i < 10 ; i++) {
            names[i] = "" ;
            scores[i] = 0 ;
        }

        ifstream myFile("highscores.bin", ios::binary) ;

        if (myFile.is_open()) {
            for (int i = 0 ; i < 10 && !myFile.eof() ; i++) {
                int length ;

                myFile.read((char*)&length, sizeof(length)) ;

                if (myFile.eof())
                    break ;

                char* temp = new char[length + 1] ;

                myFile.read(temp, length) ;

                temp[length] = '\0' ;
                names[i] = temp ;
                delete[] temp ;

                myFile.read((char*)&scores[i], sizeof(scores[i])) ;
            }
            myFile.close() ;
        }

        DrawString((BWIDTH / 2 - 70), 660, "TOP SCORES", colors[MAROON]) ;

        for (int i = 0 ; i < 10 ; i++) {
            string line = Num2Str(i + 1) + ". " + names[i] + ":  " + Num2Str(scores[i]) ;

            if (i == 9)
                DrawString((BWIDTH / 2 - 111), 600 - i * 30, line, colors[MAROON]) ;
            else
                DrawString((BWIDTH / 2 - 100), 600 - i * 30, line, colors[MAROON]) ;
        }
    }
};

#endif