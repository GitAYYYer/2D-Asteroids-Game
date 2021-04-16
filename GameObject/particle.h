#ifndef PARTICLE_H
#define PARTICLE_H
#include "../global.h"
#include "ship.h"
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
        float speed; // not used for ship particles, used only for explosion particles.
    public:
        Particle(Ship* ship);
        Particle(int x, int y, float speed, float angle);
        void draw();

        float getX();
        float getY();
        float getSize();
        float getAngle();
        int getSizeTimer();
        float getSpeed();
        void setX(float value);
        void setY(float value);
        void setSize(float value);
        void setAngle(float value);
        void setSizeTimer(int value);
        void setSpeed(float value);

        void setRGB(float r, float g, float b);
};

#endif