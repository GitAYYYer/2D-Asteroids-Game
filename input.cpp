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
    unsigned char lowerKey = tolower(key);
    if (lowerKey == KEY_ESC) {
        exit(EXIT_SUCCESS);
    }
    if (NEW_GAME) {
        NEW_GAME = false;
    }
    if (GAME_OVER) {
        RESTART_GAME = true;
    }
    if (lowerKey == ROTATE_LEFT) {
        inputShip->setIsRotatingLeft(true);
        inputShip->setIsRotatingRight(false);
    } else if (lowerKey == ROTATE_RIGHT) {
        inputShip->setIsRotatingLeft(false);
        inputShip->setIsRotatingRight(true);
    } else if (lowerKey == FORWARD) {
        inputShip->setIsMovingForward(true);
        inputParticleManager->setShipIsMoving(true);
    } else if (lowerKey == ' ') {
        inputBulletManager->setShipIsShooting(true);
    }
}

void keyboardRelease(unsigned char key, int x, int y) {
    if (GAME_OVER) {
        return;
    }
    unsigned char lowerKey = tolower(key);
    if (lowerKey == ROTATE_LEFT) {
        inputShip->setIsRotatingLeft(false);
    } else if (lowerKey == ROTATE_RIGHT) {
        inputShip->setIsRotatingRight(false);
    } else if (lowerKey == FORWARD) {
        inputShip->setIsMovingForward(false);
        inputParticleManager->setShipIsMoving(false);
    } else if (lowerKey == ' ') {
        inputBulletManager->setShipIsShooting(false);
    }
}

void mouseDown(int button, int state, int x, int y) {
    if (button == 0 && state == 0) {
        inputBulletManager->setShipIsShooting(true);
    } else if (button == 0 && state == 1) {
        inputBulletManager->setShipIsShooting(false);
    }
}