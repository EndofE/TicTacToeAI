#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "Button.h"
#include <GL/freeglut_std.h>
#include <iostream>
#include <GL/freeglut.h>

class EndScreen {
private:
    Button home;
    Button reset;
    Button continuing;

    bool setHome, setReset, setContinue; 

public:
    EndScreen() {
        setHome = false;
        setReset = false;
        setContinue = false;

        home = Button(0.0, 0.0, 0.3, 0.2, "Home", false , false);
        reset = Button(0.0, 0.3, 0.3, 0.4, "Reset", false, false);
        continuing = Button(0.0, -0.3, 0.3, 0.2, "Continue Playing", false, false);
    }

    bool homeSelected() const { return setHome; }
    bool resetSelected() const { return setReset; }
    bool continueSelected() const { return setContinue; }

    void resetBools() {
        setHome = false;
        setReset = false;
        setContinue = false;
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
            } else if(continuing.isClicked(normX, normY)) {
                resetBools();
                setContinue = true;
            }
        }
    }

    void draw() {
        home.draw();
        reset.draw();
        continuing.draw();

        glutSwapBuffers();
    }

};

#endif
