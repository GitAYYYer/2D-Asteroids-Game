#ifndef ASTEROID_H
#define ASTEROID_H
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

class Asteroid {
    private:
        // Center coordinate for asteroid
        float x, y, speed, spawnX, spawnY;
        float r, g, b;
        int radius;
        // Target coordinate (i.e. ship's X and Y) asteroid is launching to, and rotation for math stuff
        float targetX, targetY;

    public:
        int id;
        Asteroid(Ship* ship);
        ~Asteroid();
        void draw();
        void toString(int astNumber);

        float getX();
        float getY();
        float getSpawnX();
        float getSpawnY();
        float getSpeed();
        int getRadius();
        void setX(float value);
        void setY(float value);
        void setSpawnX(float value);
        void setSpawnY(float value);
        void setSpeed(float value);
        void setRadius(int value);

        float getTargetX();
        float getTargetY();
        void setTargetX(float value);
        void setTargetY(float value);
        void setRGB(float r, float g, float b);
};

#endif