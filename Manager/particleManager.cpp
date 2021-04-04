#include "particleManager.h"

ParticleManager::ParticleManager(Ship* ship) {
    this->ship = ship;
}

void ParticleManager::createShipParticles() {
    if (ship->getCollided()) {
        return;
    }
    if (shipIsMoving) {
        for (int i = 0; i < PARTICLE_AMT; i++) {
            Particle* newParticle = new Particle(ship);
            shipParticles.push_back(newParticle);
        }
    }
}

void ParticleManager::drawParticles() {
    for (int i = 0; i < shipParticles.size(); i++) {
        shipParticles[i]->draw();
    }
}

void ParticleManager::createExplosion(int x, int y) {
    // Create a random speed and random direction for each particle
    for (int i = 0; i < EXPLO_PARTICLE_AMT; i++) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = EXPLO_PARTICLE_MAX_SPEED - EXPLO_PARTICLE_MIN_SPEED;
        float r = random * diff;
        float randomSpeed = EXPLO_PARTICLE_MIN_SPEED + r;
        float randomAngle = 2.0f * M_PI * float(i) / float(EXPLO_PARTICLE_AMT);

        Particle* newParticle = new Particle(x, y, randomSpeed, randomAngle);
    }
}

std::vector<Particle*>& ParticleManager::getShipParticles() {
    return shipParticles;
}

bool ParticleManager::getShipisMoving() {
    return shipIsMoving;
}

void ParticleManager::setShipIsMoving(bool value) {
    shipIsMoving = value;
}