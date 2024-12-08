#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Button.h"
#include <iostream>
#include <GL/freeglut.h>

class StartScreen {
private:
    Button titleButton;
    Button startButton;
    Button easyAiButton;
    Button mediumAiButton;
    Button hardAiButton;
    Button AiButton;
    Button humanButton;
    Button threeButton;
    Button fourButton;
    Button fiveButton; 
    Button start;
    Button opp;
    Button bs;

    bool easy, medium, hard, none;
    bool three, four, five;
    bool game;

public:
    StartScreen() {
        easy = false;
        medium = false;
        hard = false;
        none = false;
        game = false;

        //start screen buttons
        titleButton = Button(0.0f, 0.60f, 1.00f, 0.2f, "Tic-Tac-Toe", false, false);
        startButton = Button(0.0f, -0.6f, 0.50f, 0.2f, "START", false, false);
        humanButton = Button(-0.25f, 0.2f, 0.25f, 0.2f, "1v1", false, false);
        easyAiButton = Button(0.05f, 0.2f, 0.35f, 0.2f, "Easy", false, false);
        mediumAiButton = Button(0.4f, 0.2f, 0.35f, 0.2f, "Med", false, false);
        hardAiButton = Button(0.75f, 0.2f, 0.35f, 0.2f, "Hard", false, false);
        opp = Button(-0.7f, 0.17f, 0.35f, 0.2f, "Opponent:", false, false);
        bs = Button(-0.7f, -0.23f, 0.35f, 0.2f, "Board Size:", false, false);

        //gameboard size buttons
        threeButton = Button(-0.2f, -0.2f, 0.35f, 0.2f, "3 x 3", false, false);
        fourButton = Button(0.15f, -0.2f, 0.35f, 0.2f, "4 x 4", false, false);
        fiveButton = Button(0.5f, -0.2f, 0.35f, 0.2f, "5 x 5", false, false);
    }


    void unsetOpp() {
        easy = false;
        medium = false;
        hard = false;
    }

    void unPressAi() {
        humanButton.setPressed(false);
        easyAiButton.setPressed(false);
        mediumAiButton.setPressed(false);
        hardAiButton.setPressed(false);
    }

    void unPressSize() {
        threeButton.setPressed(false);
        fourButton.setPressed(false);
        fiveButton.setPressed(false);
    }

    void resetBoardSelec() {
        three = false;
        four = false;
        five = false;
    }

    bool isEasySelected() const { return easy; }
    bool isMediumSelected() const { return medium; }
    bool isHardSelected() const { return hard; }
    bool noAi() const { return none; }

    bool threeSelected() const { return three; }
    bool fourSelected() const { return four; }
    bool fiveSelected() const { return five; }

    bool startGame() const {
        return game;
    }

    void reset() {
        game = false;
        unsetOpp();
        unPressAi();
        unPressSize();
    }

    void handleMouseClick(int button, int state, float x, float y) {
        //converts mouse coords to normal coords
        float normX = (2.0f * (x / glutGet(GLUT_WINDOW_WIDTH))) - 1.0f;
        float normY = 1.0f - (2.0f * (y / glutGet(GLUT_WINDOW_HEIGHT)));
        
        if(state == 0) {
            if(threeButton.isClicked(normX, normY)) {
                unPressSize();
                resetBoardSelec();
                threeButton.setPressed(true);
                three = true;
            } else if(fourButton.isClicked(normX, normY)) {
                unPressSize();
                resetBoardSelec();
                fourButton.setPressed(true);
                four = true;
            } else if(fiveButton.isClicked(normX, normY)) {
                unPressSize();
                resetBoardSelec();
                fiveButton.setPressed(true);
                five = true;
            }

            if(easyAiButton.isClicked(normX, normY)){
                unPressAi();
                easyAiButton.setPressed(true);
                unsetOpp();
                easy = true;
                std::cout<<"Easy AI selected"<<std::endl;
            }else if (humanButton.isClicked(normX, normY)){
                unPressAi();
                humanButton.setPressed(true);
                none = true;
                unsetOpp();
                std::cout<<"No AI selected"<<std::endl;
            }else if(mediumAiButton.isClicked(normX, normY)){
                unPressAi();
                mediumAiButton.setPressed(true);
                unsetOpp();
                medium = true;
                std::cout<<"Medium AI selected"<<std::endl;
            }else if (hardAiButton.isClicked(normX, normY)){
                unPressAi();
                hardAiButton.setPressed(true);
                unsetOpp();
                hard = true;
                std::cout<<"Hard AI selected"<<std::endl;
            }
            if(startButton.isClicked(normX, normY)) {
                game = true;
                std::cout << "Start Button Clicked!" << std::endl;
            }
        }
    }

    void draw() {
        glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        threeButton.draw(); 
        fourButton.draw(); 
        fiveButton.draw(); 
        titleButton.draw(); 
        startButton.draw(); 
        humanButton.draw(); 
        easyAiButton.draw();
        mediumAiButton.draw();
        hardAiButton.draw();
        opp.draw2();
        bs.draw2();

        glutSwapBuffers();
    }

};

#endif
