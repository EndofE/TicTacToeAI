#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include <GL/freeglut.h>
#include "stb_image.h"
#include <iostream>

class Texture {
private:
    float x;
    float y;
    float w;
    float h;
    bool selected;
    std::string imagePath;
    GLuint texture;

    void loadTexture() {
        unsigned char* imageData;
        int imageWidth;
        int imageHeight;
        int bitdepth;

        imageData = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &bitdepth, STBI_rgb_alpha);
        if (imageData == NULL) {
            std::cerr << "Failed to load texture file" << std::endl;
        } else {
            std::cout << "Texture file loaded successfully" << std::endl;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }

public:
    // parametrized constructor
    Texture(float x, float y, float w, float h, std::string imagePath) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        selected = false;
        this->imagePath = imagePath;
        loadTexture();
    }

    void draw() {
        // white/gray background for polygon
        if (selected) {
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.8f, 0.8f, 0.8f);
        }
        
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        // black border
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

            glVertex2f(x, y - h);
            glVertex2f(x, y);
        glEnd();

        // display texture
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // map texture to polygon
        glBegin(GL_POLYGON);
            // top left
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(x, y);

            // top right
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(x + w, y);

            // bottom right
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(x + w, y - h);

            // bottom left
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(x, y - h);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        }
        return false;
    }

    // setters
    void select() {
        selected = true;
    }

    void deselect() {
        selected = false;
    }
};

#endif
