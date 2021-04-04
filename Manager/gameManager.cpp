#include "gameManager.h"

Arena* arena;
Ship* ship;
Input* input;
BulletManager* bulletManager;
ParticleManager* particleManager;
WaveManager* waveManager;
TextManager* textManager;

void* wavesThread(void* arg) {
    while (true) {
        if (!NEW_GAME && !GAME_OVER) {
            waveManager->prepNextWave();
            sleep(1 * WAVE_COOLDOWN);
        }
        // if (!NEW_GAME && !GAME_OVER && waveManager->getWave() < 1) {
        //     waveManager->prepNextWave();
        //     sleep(1 * WAVE_COOLDOWN);
        // }
    }
    return 0;
}

GameManager::GameManager() {
    arena = new Arena();
    ship = new Ship();
    bulletManager = new BulletManager(ship);
    particleManager = new ParticleManager(ship);
    waveManager = new WaveManager(ship);
    textManager = new TextManager();
    input = new Input(ship, bulletManager, particleManager);
}

void GameManager::display() {
    arena->draw(ship);
    ship->draw();
    bulletManager->drawBullets();
    particleManager->drawParticles();
    waveManager->drawWave();
    textManager->drawText();
}

void GameManager::calcMovements(float deltaTime) {
    calcShipMovement(ship, deltaTime);
    calcAstMovements(waveManager->getAsteroids(), deltaTime);
    calcBulletMovements(bulletManager->getBullets(), deltaTime);
    calcPartMovements(particleManager->getShipParticles(), deltaTime);
}

void GameManager::checkCollisions() {
    MATHHANDLER_H::checkCollisions(ship, waveManager->getAsteroids(), bulletManager->getBullets(), waveManager, particleManager);
}

void GameManager::createBullets() {
    bulletManager->createBullets();
}

void GameManager::createParticles() {
    particleManager->createShipParticles();
}

void GameManager::updateText() {
    textManager->updateText();
}

void GameManager::manageWaves() {
    pthread_t tid;
    pthread_create(&tid, NULL, &wavesThread, NULL);
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