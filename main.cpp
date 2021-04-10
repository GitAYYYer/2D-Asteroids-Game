#include "Manager/gameManager.h"
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

float previousTime = 0;
GameManager gameManager;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    gameManager.display();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));
    glutSwapBuffers();
}

void idle() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - previousTime;
    // Skip the first instance of idle() where previousTime doesn't actually have a value yet.
    // Otherwise, deltaTime will be equal to just currentTime and calc methods will have an incorrect deltaTime.
    if (previousTime == 0) {
        previousTime = currentTime;
        return;
    }
    gameManager.calcMovements(deltaTime);
    gameManager.checkCollisions();
    gameManager.createBullets();
    gameManager.createParticles();
    gameManager.updateText();
    gameManager.checkRestart();

    previousTime = currentTime;
    glutPostRedisplay();
}

void init() {
    /* In this simple program these OpenGL calls only need to be done once, */
    glMatrixMode(GL_PROJECTION);
    glOrtho(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_DOWN, ORTHO_UP, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    gameManager.createThreads();
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
    glutMouseFunc(mouseDown);

    glutMainLoop();
}