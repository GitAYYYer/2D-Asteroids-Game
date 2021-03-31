#ifndef INPUT_H
#define INPUT_H
#include "GameObject/ship.h"
#include "Manager/bulletManager.h"
#include "Manager/particleManager.h"
#include "global.h"
#include <stdlib.h>
#include <stdio.h>

class Input {
    public:
        Input(Ship* ship, BulletManager* bulletManager, ParticleManager* particleManager);
};

const char FORWARD = 'w';
const char ROTATE_LEFT = 'a';
const char ROTATE_RIGHT = 'd';

void keyboardDown(unsigned char key, int x, int y);
void keyboardRelease(unsigned char key, int x, int y);
void mouseDown(int button, int state, int x, int y);

#endif