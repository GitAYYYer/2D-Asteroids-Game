#ifndef BLACKHOLE_H
#define BLACKHOLE_H
#include "../global.h"
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

class BlackHole {
    private:
        float x, y, theta;
        int currentRadius, startingRadius, lastPulse;
    
    public:
        BlackHole();
        void draw();
        void reset();

        float getX();
        float getY();
        float getTheta();
        int getCurrentRadius();
        int getStartingRadius();
        int getLastPulse();
        void setX(float value);
        void setY(float value);
        void setTheta(float value);
        void setCurrentRadius(int value);
        void setStartingRadius(int value);
        void setLastPulse(int value);
};

float getRandomFloat(float min, float max);

#endif