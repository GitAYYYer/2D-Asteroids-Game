#include "bulletManager.h"

BulletManager::BulletManager(Ship* ship) {
    this->ship = ship;
    this->lastBulletTimer = 0;
}

BulletManager::BulletManager(TentacleMonster* tm) {
    this->tm = tm;
    this->lastBulletTimer = 0;
}

void BulletManager::createBullets() {
    if (ship == nullptr) {
        return;
    }
    if (ship->getCollided() || this->lastBulletTimer + SHIP_FIRING_RATE > glutGet(GLUT_ELAPSED_TIME)) {
        return;
    }
    // Only if ship is shooting and last bullet was at least X ms ago, create a bullet
    if (shipIsShooting) {
        this->lastBulletTimer = glutGet(GLUT_ELAPSED_TIME);
        // Bullet* newBullet = new Bullet(ship);
        Bullet* newBullet = new Bullet(ship->getX() - (sinf(ship->getCurrentRotation() * M_PI/180) * 40), 
                                        ship->getY() + (cosf(ship->getCurrentRotation() * M_PI/180) * 40),
                                        BULLET_SPEED,
                                        ship->getCurrentRotation(),
                                        BULLET_SIZE,
                                        BULLET_R,
                                        BULLET_G,
                                        BULLET_B);
        // Bullet* newBullet2 = new Bullet(ship->getX() - (sinf(ship->getCurrentRotation() * M_PI/180) * 40), 
        //                                 ship->getY() + (cosf(ship->getCurrentRotation() * M_PI/180) * 40),
        //                                 BULLET_SPEED,
        //                                 ship->getCurrentRotation() - 10,
        //                                 BULLET_SIZE,
        //                                 BULLET_R,
        //                                 BULLET_G,
        //                                 BULLET_B);
        bullets.push_back(newBullet);
        // bullets.push_back(newBullet2);
    }
}

void BulletManager::createBossBullets(float x, float y, float speed, float angle, int size, float r, float g, float b) {
    Bullet* newBullet = new Bullet(x, y, speed, angle, size, r, g, b);
    bullets.push_back(newBullet);
}

void BulletManager::drawBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->draw();
    }
}

void BulletManager::reset() {
    lastBulletTimer = 0;
    bullets.clear();
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