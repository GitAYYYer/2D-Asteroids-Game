#ifndef ASTEROID_H
#define ASTEROID_H
#include "asteroidVariation.h"
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

using std::vector;
#define COUNTER_CLOCKWISE 0
#define CLOCKWISE 1

class Asteroid {
    private:
        // Center coordinates for asteroid, speed, and its initial X,Y coords
        float x, y, speed, spawnX, spawnY;
        float r, g, b;
        int radius, rotateDirection;
        // Target coordinate (i.e. ship's X and Y) asteroid is launching to
        float targetX, targetY;
        float currentRotation, rotateSpeed;
        // Holds tuples of where to start the variations, for how many segments, and how much to add to the X and Y.
        vector<AsteroidVariation> variations;

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
        float getCurrentRotation();
        int getRotateDirection();
        float getRotateSpeed();
        void setX(float value);
        void setY(float value);
        void setSpawnX(float value);
        void setSpawnY(float value);
        void setSpeed(float value);
        void setRadius(int value);
        void setCurrentRotation(float value);
        void setRotateDirection(int value);
        void setRotateSpeed(float value);

        float getTargetX();
        float getTargetY();
        void setTargetX(float value);
        void setTargetY(float value);
        void setRGB(float r, float g, float b);
};

float getRandFloat(float min, float max);

#endif