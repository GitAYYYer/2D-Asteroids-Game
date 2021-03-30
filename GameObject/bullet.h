#ifndef BULLET_H
#define BULLET_H
#include "../global.h"
#include "ship.h"
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

class Bullet {
    private:
        float x, y, speed, angle, r, g, b;
        int size;
    public:
        Bullet(Ship* ship);
        void draw();

        float getX();
        float getY();
        float getSpeed();
        float getAngle();
        int getSize();

        void setX(float value);
        void setY(float value);
        void setSpeed(float value);
        void setAngle(float value);
        void setSize(int value);
        void setRGB(float r, float g, float b);
};

#endif