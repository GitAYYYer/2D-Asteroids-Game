#include <stdlib.h>
#include <stdio.h>
#include "GameObject/arena.h"
#include "GameObject/ship.h"
#include "Manager/particleManager.h"
#include "Manager/waveManager.h"
#include "global.h"
#include "input.h"
#include "mathHandler.h"
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

// Delta Related
float previousTime = 0;

Arena arena;
Ship ship;
ParticleManager particleManager(&ship);
WaveManager waveMananger(&ship);
Input input(&ship, &particleManager);

void* threadProc(void* arg) {
    while (!GAME_OVER) {
        printf("Preparing wave %d\n", waveMananger.wave + 1);
        waveMananger.prepNextWave();
        sleep(1 * WAVE_COOLDOWN);
    }
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    arena.drawArena(&ship);
    ship.drawShip(&ship);
    particleManager.drawParticles();
    waveMananger.drawWave();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));
    glutSwapBuffers();
}

void idle() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - previousTime;
    // Skip the first instance of idle() where previousTime doesn't actually have a value yet.
    // Otherwise, deltaTime will be equal to just currentTime and calc methods will have an incorrect timeDelta.
    if (previousTime == 0) {
        previousTime = currentTime;
        return;
    }
    calcShipMovement(&ship, deltaTime);
    calcAstMovements(waveMananger.getAsteroids(), deltaTime);
    calcPartMovements(particleManager.getParticles(), deltaTime);
    // checkCollisions(&ship, waveMananger.getAsteroids());
    particleManager.createParticles();

    previousTime = currentTime;
    glutPostRedisplay();
}

void init() {
    /* In this simple program these OpenGL calls only need to be done once, */
    glMatrixMode(GL_PROJECTION);
    glOrtho(-960.0, 960.0, -540.0, 540.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // Create thread for managing waves
    pthread_t tid;
    pthread_create(&tid, NULL, &threadProc, NULL);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Assignment 1 - 2D Asteroids");
    glutFullScreen();
    init();

    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardRelease);

    glutMainLoop();
}