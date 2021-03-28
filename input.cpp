#include "input.h"

Ship* inputShip; 
ParticleManager* inputParticleManager;
Input::Input(Ship* shipArg, ParticleManager* pmArg) {
    inputShip = shipArg;
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