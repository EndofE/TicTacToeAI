#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "Button.h"
#include <GL/freeglut_std.h>
#include <iostream>
#include <GL/freeglut.h>
#include "Game.h"

class EndScreen {
private:
    Game* game;
    Button home;
    Button reset;

    Button playerX;
    Button playerO;
    Button tie;

    bool setHome, setReset, setContinue; 

public:
    EndScreen(Game* g) : game(g) {
        setHome = false;
        setReset = false;
        // setContinue = false;

        home = Button(-0.3, 0.0, 0.4, 0.2, "Home", false , false);
        reset = Button(0.3, 0.0, 0.4, 0.2, "Reset", false, false);

        playerX = Button(0.0, 0.6, 0.8, 0.2, "Player X Won!", false, false);
        playerO = Button(0.0, 0.6, 0.8, 0.2, "Player O Won!", false, false);
        tie = Button(0.0, 0.6, 0.8, 0.2, "It was a draw...", false, false);
        // continuing = Button(0.0, -0.4, 0.9, 0.2, "Continue Playing", false, false);
    }

    bool homeSelected() const { return setHome; }
    bool resetSelected() const { return setReset; }
    bool continueSelected() const { return setContinue; }

    void resetBools() {
        setHome = false;
        setReset = false;
        // setContinue = false;
    }

    void handleMouseClick(int button, int state, float x, float y) {
        //converts mouse coords to normal coords
        float normX = (2.0f * (x / glutGet(GLUT_WINDOW_WIDTH))) - 1.0f;
        float normY = 1.0f - (2.0f * (y / glutGet(GLUT_WINDOW_HEIGHT)));
        
        if(state == 0) {
            if(home.isClicked(normX, normY)) {
                resetBools();
                setHome = true;
            } else if(reset.isClicked(normX, normY)) {
                resetBools();
                setReset = true;
            // } else if(continuing.isClicked(normX, normY)) {
            //     resetBools();
            //     setContinue = true;
            }
        }
    }

    void draw() {
        glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        home.draw();
        reset.draw();
        std::cout<<"game: "<<game->winner<<std::endl;

        if(game->returnWinner() == 1) {
            std::cout<<"Player X Won"<<std::endl;
            playerX.draw2();
        } else if(game->returnWinner() == 2) {
            std::cout<<"Player O Won"<<std::endl;
            playerO.draw2();
        } else {
            std::cout<<"Tied"<<std::endl;
            tie.draw2();
        }

        glutSwapBuffers();
    }

};

#endif
