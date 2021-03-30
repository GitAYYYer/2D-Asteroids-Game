#include "waveManager.h"

WaveManager::WaveManager(Ship* ship) {
    this->ship = ship;
    this->wave = 0;
}

void WaveManager::populateAsteroids() {
    for (int i = 0; i < wave; i++) {
        Asteroid* newAsteroid = new Asteroid(ship);
        asteroids.push_back(newAsteroid);
    }
}

void WaveManager::drawWave() {
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i]->draw();
    }
}

void WaveManager::prepNextWave() {
    this->wave += 1;
    populateAsteroids();
}

std::vector<Asteroid*>& WaveManager::getAsteroids() {
    return asteroids;
}