#include "bulletManager.h"

BulletManager::BulletManager(Ship* ship) {
    this->ship = ship;
    this->lastBulletTimer = 0;
}

void BulletManager::createBullets() {
    if (ship->getCollided() || this->lastBulletTimer + SHIP_FIRING_RATE > glutGet(GLUT_ELAPSED_TIME)) {
        return;
    }
    // Only if ship is shooting and last bullet was at least X ms ago, create a bullet
    if (shipIsShooting) {
        this->lastBulletTimer = glutGet(GLUT_ELAPSED_TIME);
        Bullet* newBullet = new Bullet(ship);
        bullets.push_back(newBullet);
    }
}

void BulletManager::drawBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->draw();
    }
}

void BulletManager::reset() {
    lastBulletTimer = 0;
}

std::vector<Bullet*>& BulletManager::getBullets() {
    return bullets;
}

bool BulletManager::getShipIsShooting() {
    return shipIsShooting;
}

int BulletManager::getLastBulletTimer() {
    return lastBulletTimer;
}

void BulletManager::setShipIsShooting(bool value) {
    shipIsShooting = value;
}

void BulletManager::setLastBulletTimer(int value) {
    lastBulletTimer = value;
}