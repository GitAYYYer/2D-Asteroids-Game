#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#include "../GameObject/particle.h"
#include "../global.h"
#include "vector"

class ParticleManager {
    private:
        std::vector<Particle*> particles;
        Ship* ship;
        bool shipIsMoving;
    public:
        ParticleManager(Ship* ship);
        void createParticles();
        void drawParticles();
        std::vector<Particle*>& getParticles();

        bool getShipisMoving();
        void setShipIsMoving(bool value);
};
#endif