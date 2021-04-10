#include "gameManager.h"

Arena* arena;
Ship* ship;
BlackHole* blackHole;
Input* input;
BulletManager* bulletManager;
ParticleManager* particleManager;
WaveManager* waveManager;
TextManager* textManager;
TentacleMonster* tentacleMonster;

void* wavesThread(void* arg) {
    while (true) {
        if (!NEW_GAME && !GAME_OVER && !FIGHTING_BOSS) {
            waveManager->prepNextWave();
            sleep(1 * WAVE_COOLDOWN);

            if (waveManager->getWave() == 3) {
                FIGHTING_BOSS = true;
            }
        }
        // if (!NEW_GAME && !GAME_OVER && waveManager->getWave() < 1) {
        //     waveManager->prepNextWave();
        //     sleep(1 * WAVE_COOLDOWN);
        // }
    }
    return 0;
}

void* manageTmArmsThread(void* arg) {
    float secondsSleep = 0.01;
    while (tentacleMonster->getHp() > 0) {
        tentacleMonster->changeArmFluct();
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

    tentacleMonster = new TentacleMonster();
}

void GameManager::display() {
    arena->draw(ship);
    ship->draw();
    blackHole->draw();
    bulletManager->drawBullets();
    particleManager->drawParticles();
    waveManager->drawWave();
    textManager->drawText();

    if (FIGHTING_BOSS) {
        tentacleMonster->draw();
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

    if (FIGHTING_BOSS) {
        calcTentacleMonsterMovement(tentacleMonster, deltaTime);
    }
}

void GameManager::checkCollisions() {
    MATHHANDLER_H::checkCollisions(ship, blackHole, waveManager->getAsteroids(), bulletManager->getBullets(), waveManager, particleManager);
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
}

void GameManager::checkRestart() {
    if (RESTART_GAME) {
        printf("I have just restarted.\n");
        RESTART_GAME = false;
        GAME_OVER = false;
        SCORE = 0;
        ship->reset();
        waveManager->reset();
        textManager->reset();
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