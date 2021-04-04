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

void WaveManager::reset() {
    this->wave = 0;
    asteroids.clear();
}

void WaveManager::splitAsteroid(int counter, float sinD(float), float cosD(float)) {
    Asteroid* deadAsteroid = asteroids[counter];
    int deadRadius = deadAsteroid->getRadius();
    float deadX = deadAsteroid->getX();
    float deadY = deadAsteroid->getY();
    float deadTheta = deadAsteroid->getTheta();
    float deadSpeed = deadAsteroid->getSpeed();

    Asteroid* leftAsteroid = new Asteroid(ship);
    Asteroid* rightAsteroid = new Asteroid(ship);
        // float xTranslation = asteroids[i]->getSpeed() * deltaTime * cosD(theta);
        // float yTranslation = asteroids[i]->getSpeed() * deltaTime * sinD(theta);

    int astOffset = 500;
    float leftAstX = deadX + deadSpeed * astOffset * cosD(deadTheta - 90);
    float leftAstY = deadY + deadSpeed * astOffset * sinD(deadTheta - 90);
    float leftAstTargetX = leftAstX + deadSpeed * astOffset * cosD(deadTheta - 45);
    float leftAstTargetY = leftAstY + deadSpeed * astOffset * sinD(deadTheta - 45);
    float rightAstX = deadX + deadSpeed * astOffset * cosD(deadTheta + 90);
    float rightAstY = deadY + deadSpeed * astOffset * sinD(deadTheta + 90);
    float rightAstTargetX = rightAstX + deadSpeed * astOffset * cosD(deadTheta + 45);
    float rightAstTargetY = rightAstY + deadSpeed * astOffset * sinD(deadTheta + 45);

    leftAsteroid->setX(leftAstX);
    leftAsteroid->setY(leftAstY);
    leftAsteroid->setTargetX(leftAstTargetX);
    leftAsteroid->setTargetY(leftAstTargetY);
    leftAsteroid->setTheta(deadTheta - 45);
    leftAsteroid->setRadius(deadRadius/2);
    leftAsteroid->setSpeed(deadSpeed);
    leftAsteroid->setHP(deadRadius/2 * 2.1);
    leftAsteroid->setFromSplit(true);

    rightAsteroid->setX(rightAstX);
    rightAsteroid->setY(rightAstY);
    rightAsteroid->setTargetX(rightAstTargetX);
    rightAsteroid->setTargetY(rightAstTargetY);
    rightAsteroid->setTheta(deadTheta + 45);
    rightAsteroid->setRadius(deadRadius/2);
    rightAsteroid->setSpeed(deadSpeed);
    rightAsteroid->setHP(deadRadius/2 * 2.1);
    rightAsteroid->setFromSplit(true);

    asteroids.push_back(leftAsteroid);
    asteroids.push_back(rightAsteroid);
}

std::vector<Asteroid*>& WaveManager::getAsteroids() {
    return asteroids;
}

int WaveManager::getWave() {
    return wave;
}