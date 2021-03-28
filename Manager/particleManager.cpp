#include "particleManager.h"

ParticleManager::ParticleManager(Ship* ship) {
    this->ship = ship;
}

void ParticleManager::createParticles() {
    if (ship->getCollided()) {
        return;
    }
    if (shipIsMoving) {
        for (int i = 0; i < PARTICLE_AMT; i++) {
            Particle* newParticle = new Particle(ship);
            particles.push_back(newParticle);
        }
    }
}

void ParticleManager::drawParticles() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->draw();
    }
}

std::vector<Particle*>& ParticleManager::getParticles() {
    return particles;
}

bool ParticleManager::getShipisMoving() {
    return shipIsMoving;
}

void ParticleManager::setShipIsMoving(bool value) {
    shipIsMoving = value;
}