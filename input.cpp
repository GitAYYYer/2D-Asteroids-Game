#include "input.h"

Ship* inputShip; 
BulletManager* inputBulletManager;
ParticleManager* inputParticleManager;
Input::Input(Ship* shipArg, BulletManager* bmArg, ParticleManager* pmArg) {
    inputShip = shipArg;
    inputBulletManager = bmArg;
    inputParticleManager = pmArg;
}

void keyboardDown(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(EXIT_SUCCESS);
    }
    if (GAME_OVER) {
        return;
    }
    if (key == ROTATE_LEFT) {
        inputShip->setIsRotatingLeft(true);
        inputShip->setIsRotatingRight(false);
    } else if (key == ROTATE_RIGHT) {
        inputShip->setIsRotatingLeft(false);
        inputShip->setIsRotatingRight(true);
    } else if (key == FORWARD) {
        inputShip->setIsMovingForward(true);
        inputParticleManager->setShipIsMoving(true);
    }
}

void keyboardRelease(unsigned char key, int x, int y) {
    if (GAME_OVER) {
        return;
    }
    if (key == ROTATE_LEFT) {
        inputShip->setIsRotatingLeft(false);
    } else if (key == ROTATE_RIGHT) {
        inputShip->setIsRotatingRight(false);
    } else if (key == FORWARD) {
        inputShip->setIsMovingForward(false);
        inputParticleManager->setShipIsMoving(false);
    }
}

void mouseDown(int button, int state, int x, int y) {
    if (button == 0 && state == 0) {
        inputBulletManager->setShipIsShooting(true);
    } else if (button == 0 && state == 1) {
        inputBulletManager->setShipIsShooting(false);
    }
}