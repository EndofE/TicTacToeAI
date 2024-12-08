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

    bool gameStarted = false;
    bool gameEnded = false;

public:
    Controller() : gameStarted(false), game(), end(&game) {}

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
        if(!gameStarted && !gameEnded) {
            start.handleMouseClick(button, state, x, y);
            if(start.startGame()) {
                switch (start.amountS()) {
                
                case 3:
                    game.resizeBoard(3);
                    break;
                case 4:
                    game.resizeBoard(4);
                    break;
                case 5:
                    game.resizeBoard(5);
                    break;
                default: std::cout<<"Errors, 3 x 3" <<std::endl;
                game.resizeBoard(3);
                }

                if(start.isEasySelected()) {
                    game.setEasyAI(true);
                } else if(start.isMediumSelected()) {
                    game.setMediumAI(true);
                } else if(start.isHardSelected()) {
                    game.setHardAI(true);
                }else if(start.noAi()) {
                    game.setNoAi(true);
                }
                gameStarted = true;
                game.resetGame();
            }
        } else if(gameStarted && !gameEnded){
            game.handleMouseClick(button, state, x, y);
            if(game.gameDone()) {
                gameEnded = true;
                gameStarted = false;
            }
        } else if(!gameStarted && gameEnded) {
            end.handleMouseClick(button, state, x, y);
            if(end.homeSelected()) {
                gameEnded = false;
                gameStarted = false;
                game.resetGame();
                start.reset();
            } else if(end.resetSelected()) {
                gameStarted = true;
                gameEnded = false;
                game.resetGame();
            }
        }
    }
    
    void leftMouseUp(float x, float y) {}

    ~Controller(){}
    
};

#endif
