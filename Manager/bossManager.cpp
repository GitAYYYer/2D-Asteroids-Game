#include "bossManager.h"

BossManager::BossManager(Ship* ship) {
    this->ship = ship;
    this->tm = new TentacleMonster();
    this->bossBullets = new BulletManager(this->tm);
    this->fightingBoss = false;
}

// 1/4 chance to do something, every X seconds (X determined by gameManager thread)
void BossManager::performAction() {
    int chance = rand() % 4;
    if (chance) {
        int shoot = rand() % 2;
        if (shoot) {
            // Get angle the armEndPt makes with ship, so that bullets go towards ship
            for (int i = 0; i < tm->getArmEndPtCoords().size(); i++) {
                float armX = get<0>(tm->getArmEndPtCoords()[i]);
                float armY = get<1>(tm->getArmEndPtCoords()[i]);
                float angle = atan2(armY - ship->getY(), armX - ship->getX()) * 180/M_PI;
                bossBullets->createBossBullets(armX, armY, angle + 90);   
            }
        } else {
            int xWidth = ARENA_WIDTH/2;
            int yWidth = ARENA_HEIGHT/2;
            int randX = (rand() % (int)ARENA_WIDTH) - ARENA_WIDTH/2;
            int randY = (rand() % (int)ARENA_HEIGHT) - ARENA_HEIGHT/2;

            float newAngle = atan2(randY - tm->getY(), randX - tm->getX()) * 180/M_PI;
            tm->setTheta(newAngle);
            tm->setSpeed(0.1);
        }
    }
}

void BossManager::reset() {
    delete tm;
    delete bossBullets;
    this->tm = new TentacleMonster();
    this->bossBullets = new BulletManager(this->tm);
    this->fightingBoss = false;
}

void BossManager::setNewBoss() {
    delete tm;
    this->tm = new TentacleMonster();
}

bool BossManager::getFightingBoss() {
    return fightingBoss;
}

void BossManager::setFightingBoss(bool value) {
    fightingBoss = value;
}

TentacleMonster* BossManager::getTM() {
    return tm;
}

BulletManager* BossManager::getBossBulletManager() {
    return bossBullets;
}