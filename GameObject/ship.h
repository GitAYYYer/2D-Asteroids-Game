#ifndef SHIP_H
#define SHIP_H
#include "../global.h"
#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

class Ship {
    private:
        float x, y, currentRotation, currentSpeed;
        bool isMovingForward, isRotatingLeft, isRotatingRight, collided;

    public:
        Ship();
        void draw();
        void reset();

        float getX();
        float getY();
        float getCurrentRotation();
        float getCurrentSpeed();
        void setX(float value);
        void setY(float value);
        void setCurrentRotation(float value);
        void setCurrentSpeed(float value);

        bool getIsMovingForward();
        bool getIsRotatingLeft();
        bool getIsRotatingRight();
        void setIsMovingForward(bool value);
        void setIsRotatingLeft(bool value);
        void setIsRotatingRight(bool value);

        bool getCollided();
        void setCollided(bool value);
};

#endif