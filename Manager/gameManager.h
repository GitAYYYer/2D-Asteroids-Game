#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "../GameObject/arena.h"
#include "../GameObject/ship.h"
#include "../GameObject/blackhole.h"
#include "../global.h"
#include "../input.h"
#include "../mathHandler.h"
#include "bulletManager.h"
#include "particleManager.h"
#include "waveManager.h"
#include "textManager.h"
#include "vector"
#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#endif

using std::vector;

class GameManager {
    private:
    public:
        GameManager(); // I want to use just this manager, which creates everything else.
        void display();
        void calcMovements(float deltaTime);
        void checkCollisions();
        void createBullets();
        void createParticles();
        void handleBlackHole();
        void updateText();
        void manageWaves();
        void checkRestart();

        Ship* getShip();
        Input* getInput();
        BulletManager* getBulletManager();
        ParticleManager* getParticleManager();
        WaveManager* getWaveManager();
        TextManager* getTextManager();
};

#endif