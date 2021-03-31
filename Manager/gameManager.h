#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "../GameObject/ship.h"
#include "waveManager.h"
#include "textManager.h"
#include "vector"

using std::vector;

class GameManager {
    private:
        Ship* ship;
        WaveManager* waveManager;
        TextManager* textManager;
    public:
        GameManager(Ship* ship, WaveManager* waveManager, TextManager* textManager);
};

#endif