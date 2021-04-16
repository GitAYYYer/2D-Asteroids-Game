#include "gameManager.h"

Arena* arena;
Ship* ship;
BlackHole* blackHole;
Input* input;
BulletManager* bulletManager;
ParticleManager* particleManager;
WaveManager* waveManager;
TextManager* textManager;
BossManager* bossManager;

// Every random amt of seconds, shoot bullets or move
void* handleBossFight(void* arg) {
    float secondsSleep = 1;
    while (true) {
        if (bossManager->getFightingBoss()) {
            bossManager->performAction();
            sleep(secondsSleep);
        }
    }
    return 0;
}

void* wavesThread(void* arg) {
    while (true) {
        if (!NEW_GAME && !GAME_OVER && !bossManager->getFightingBoss()) {
            waveManager->prepNextWave();
            sleep(1 * WAVE_COOLDOWN);

            if (waveManager->getWave() % 5 == 0 && waveManager->getWave() != 0) {
                bossManager->setFightingBoss(true);
            }
        }
    }
    return 0;
}

void* manageTmArmsThread(void* arg) {
    float secondsSleep = 0.01;
    while (bossManager->getTM()->getHp() > 0) {
        bossManager->getTM()->changeArmFluct();
        usleep(secondsSleep * 1000000);
    }
    return 0;
}

GameManager::GameManager() {
    arena = new Arena();
    ship = new Ship();
    blackHole = new BlackHole();
    bulletManager = new BulletManager(ship);
    particleManager = new ParticleManager(ship);
    waveManager = new WaveManager(ship);
    textManager = new TextManager();
    input = new Input(ship, bulletManager, particleManager);

    bossManager = new BossManager(ship);
}

void GameManager::display() {
    arena->draw(ship);
    ship->draw();
    blackHole->draw();
    bulletManager->drawBullets();
    particleManager->drawParticles();
    waveManager->drawWave();
    textManager->drawText();

    if (bossManager->getFightingBoss()) {
        bossManager->getTM()->draw();
        bossManager->getBossBulletManager()->drawBullets();
    }
}

void GameManager::calcMovements(float deltaTime) {
    if (NEW_GAME) {
        return;
    }
    calcShipMovement(ship, deltaTime);
    calcAstMovements(waveManager->getAsteroids(), deltaTime);
    calcBulletMovements(bulletManager->getBullets(), deltaTime);
    calcPartMovements(particleManager->getShipParticles(), particleManager->getExploParticles(), deltaTime);
    handleBlackHole();

    if (bossManager->getFightingBoss()) {
        calcTentacleMonsterMovement(bossManager->getTM(), deltaTime);
        calcBossBulletMovement(bossManager->getBossBulletManager()->getBullets(), deltaTime);
    }
}

void GameManager::checkCollisions() {
    MATHHANDLER_H::checkCollisions(ship, blackHole, waveManager->getAsteroids(), bulletManager->getBullets(), waveManager, particleManager);
    
    if (bossManager->getFightingBoss()) {
        calcBossCollision(bossManager, ship, waveManager->getAsteroids(), bulletManager->getBullets(), particleManager);
        calcBossBulletsCollision(ship, blackHole, bossManager->getBossBulletManager()->getBullets());
    }
    if (bossManager->getTM()->getHp() <= 0 && bossManager->getFightingBoss()) {
        for (int i = 0; i < 5; i++) {
            int xOffset = (rand() % 80) - 40;
            int yOffset = (rand() % 160) - 160;
            particleManager->createExplosion(bossManager->getTM()->getX() + xOffset, bossManager->getTM()->getY() + yOffset);
        }
        SCORE += 50;
        if (SHIP_FIRING_RATE - 50 > 0) {
            SHIP_FIRING_RATE -= 50;
        }
        bossManager->setFightingBoss(false);
        bossManager->setNewBoss();
    }
}

void GameManager::createBullets() {
    bulletManager->createBullets();
}

void GameManager::createParticles() {
    particleManager->createShipParticles();
}

void GameManager::handleBlackHole() {
    calcBlackHolePulse(blackHole);
}

void GameManager::updateText() {
    textManager->updateText();
}

void GameManager::createThreads() {
    pthread_t tid;
    pthread_create(&tid, NULL, &wavesThread, NULL);

    pthread_t tid2;
    pthread_create(&tid2, NULL, &manageTmArmsThread, NULL);

    pthread_t tid3;
    pthread_create(&tid3, NULL, &handleBossFight, NULL);
}

void GameManager::checkRestart() {
    if (RESTART_GAME) {
        RESTART_GAME = false;
        GAME_OVER = false;
        SCORE = 0;
        ship->reset();
        blackHole->reset();
        bulletManager->reset();
        waveManager->reset();
        textManager->reset();
        bossManager->reset();
    }
}

Ship* GameManager::getShip() {
    return ship;
}

Input* GameManager::getInput() {
    return input;
}

BulletManager* GameManager::getBulletManager() {
    return bulletManager;
}

ParticleManager* GameManager::getParticleManager() {
    return particleManager;
}

WaveManager* GameManager::getWaveManager() {
    return waveManager;
}

TextManager* GameManager::getTextManager() {
    return textManager;
}