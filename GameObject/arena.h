#ifndef ARENA_H
#define ARENA_H
#include "../global.h"
#include "ship.h"
#include "stdio.h"
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

class Arena {
    private:
        float xCenter;
        float yCenter;
        // Radius of the circle from the arena that spawns asteroids
        float orbitRadius;
    public:
        Arena();
        void draw(Ship* ship);
        void checkWarningDistance(Ship* ship);
        float getOrbitRadius();
};

#endif