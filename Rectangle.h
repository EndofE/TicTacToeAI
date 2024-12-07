#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>
#include "Shape.h"
#include "Color.h"

enum RectState {FREE, MOVEO, MOVEX};

class Rectangle : public Shape {
    float w;
    float h;
    bool solid;
    bool hasX;
    bool hasO;
    RectState form;
    bool play;

public:
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        selected = false;
        solid = true;
        play = false;
        form = FREE;
    }

    Rectangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
        solid = true;
        play = false;
    }

    Rectangle(float x, float y, float w, float h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
        solid = false;
        play = false;
        form = FREE;
    }

    // getters
    float getW() {
        return w;
    }
    
    float getH() {
        return h;
    }

    // setters
    void setW(float w) {
        this->w = w;
    }
    
    void setH(float h) {
        this->h = h;
    }
  
    bool isEmpty() {
        return form == FREE;
    }

    void playX() {
        
        form = MOVEX;
    }

    void playO() {
        
        form = MOVEO;
    }

     
     RectState getState() {
        return form;
    } 
    

    void draw() {
        if (!solid){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glColor3f(color.getR(), color.getG(), color.getB());
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (selected) {
            Rectangle outer(x + 0.02f, y - 0.02f, w - 0.04f, h - 0.04f, Color(1.0f, 1.0f, 1.0f));
            Rectangle inner(x + 0.04f, y - 0.04f, w - 0.08f, h - 0.08f, color);
            outer.draw();
            inner.draw();
        }

        if (form == MOVEX) {
           glBegin(GL_LINES);
                glVertex2f(x + 0.1f, y - 0.1f);
                glVertex2f(x + w - 0.1f, y - h + 0.1f);

                glVertex2f(x + w - 0.1f, y - 0.1f);
                glVertex2f(x + 0.1f, y - h + 0.1f);
            glEnd();
        } else if (form == MOVEO) {
            glBegin(GL_LINES);
                float inc = (2 * M_PI) / 60;
                for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
                    glVertex2f((x + (w / 2)) + (w / 2 - 0.1f) * cos(theta), (y - (h / 2)) + (h / 2 - 0.1f) * sin(theta));
                    glVertex2f((x + (w / 2)) + (w / 2 - 0.1f) * cos(theta + inc), (y - (h / 2)) + (h / 2 - 0.1f) * sin(theta + inc));
                }
            glEnd();
        }
        
    }
    

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};

#endif
