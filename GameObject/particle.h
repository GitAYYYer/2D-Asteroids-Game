#ifndef PARTICLE_H
#define PARTICLE_H
#include "../global.h"
#include "../GameObject/ship.h"
#include "random"
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

class Particle {
    private:
        float x, y;
        float r, g, b;
        float size, angle;
        int sizeTimer;
    public:
        Particle(Ship* ship);
        void draw();

        float getX();
        float getY();
        float getSize();
        float getAngle();
        int getSizeTimer();
        void setX(float value);
        void setY(float value);
        void setSize(float value);
        void setAngle(float value);
        void setSizeTimer(int value);

        void setRGB(float r, float g, float b);
};

#endif