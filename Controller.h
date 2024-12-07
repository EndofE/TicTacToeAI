#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"
#include "Game.h"
#include "StartScreen.h"
#include "EndScreen.h"

class Controller : public AppController{
    Game game;
    StartScreen start;
    EndScreen end;

    bool gameStarted;
    bool gameEnded;

public:
    Controller() : gameStarted(false) {}

    void render() {
        if(!gameStarted && !gameEnded) {
            start.draw();
        } else if(gameStarted && !gameEnded){
            game.draw();
        } else if(!gameStarted && gameEnded) {
            end.draw();
        }
    }

    void leftMouseDown(int button, int state, float x, float y) {
        if(!gameStarted) {
            start.handleMouseClick(button, state, x, y);
            if(start.startGame()) {
                if(start.threeSelected()) {
                    game.resizeBoard(3);
                } else if(start.fourSelected()) {
                    game.resizeBoard(4);
                } else if(start.fiveSelected()) {
                    game.resizeBoard(5);
                }

                if(start.isEasySelected()) {
                    game.setEasyAI(true);
                } else if(start.isMediumSelected()) {
                    game.setMediumAI(true);
                } else if(start.isHardSelected()) {
                    game.setHardAI(true);
                }
                gameStarted = true;
                game.resetGame();
            }
        } else {
            game.handleMouseClick(button, state, x, y);
            
        }
    }
    
    void leftMouseUp(float x, float y) {}

    ~Controller(){}
    
};

#endif
