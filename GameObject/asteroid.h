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

class Asteroid {
    private:
        float x, y, speed, spawnX, spawnY, theta, hp;
        float r, g, b;
        int radius, rotateDirection;
        float targetX, targetY;
        float currentRotation, rotateSpeed;
        bool inArena;
        bool horizontalBounce, verticalBounce, asteroidBounce;
        bool fromSplit;
        // Holds info of where to start the variations, for how many segments, and how much to add to the X and Y.
        vector<AsteroidVariation> variations;

    public:
        Asteroid(Ship* ship);
        ~Asteroid();
        void draw();
        void toString(int astNumber);

        float getX();
        float getY();
        float getSpawnX();
        float getSpawnY();
        float getTheta();
        float getHP();
        float getSpeed();
        int getRadius();
        float getCurrentRotation();
        int getRotateDirection();
        float getRotateSpeed();
        bool getInArena();
        bool getHorizontalBounce();
        bool getVerticalBounce();
        bool getAsteroidBounce();
        bool getFromSplit();
        void setX(float value);
        void setY(float value);
        void setHP(float value);
        void setSpawnX(float value);
        void setSpawnY(float value);
        void setTheta(float value);
        void setSpeed(float value);
        void setRadius(int value);
        void setCurrentRotation(float value);
        void setRotateDirection(int value);
        void setRotateSpeed(float value);
        void setInArena(bool value);
        void setHorizontalBounce(bool value);
        void setVerticalBounce(bool value);
        void setAsteroidBounce(bool value);
        void setFromSplit(bool value);

        float getTargetX();
        float getTargetY();
        void setTargetX(float value);
        void setTargetY(float value);
        void setRGB(float r, float g, float b);
};

float getRandFloat(float min, float max);

#endif