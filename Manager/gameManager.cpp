#include "gameManager.h"

GameManager::GameManager(Ship* ship, WaveManager* waveManager, TextManager* textManager) {
    this->ship = ship;
    this->waveManager = waveManager;
    this->textManager = textManager;
}