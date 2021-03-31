#include "gameManager.h"

Arena* arena;
Ship* ship;
Input* input;
BulletManager* bulletManager;
ParticleManager* particleManager;
WaveManager* waveManager;
TextManager* textManager;

void* wavesThread(void* arg) {
    while (!GAME_OVER) {
        printf("Preparing wave %d\n", waveManager->getWave() + 1);
        waveManager->prepNextWave();
        sleep(1 * WAVE_COOLDOWN);
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
    calcPartMovements(particleManager->getParticles(), deltaTime);
}

void GameManager::checkCollisions() {
    MATHHANDLER_H::checkCollisions(ship, waveManager->getAsteroids(), bulletManager->getBullets());
}

void GameManager::createBullets() {
    bulletManager->createBullets();
}

void GameManager::createParticles() {
    particleManager->createParticles();
}

void GameManager::updateText() {
    textManager->updateText();
}

void GameManager::manageWaves() {
    pthread_t tid;
    pthread_create(&tid, NULL, &wavesThread, NULL);
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