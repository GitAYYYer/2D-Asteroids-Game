#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#include "../GameObject/particle.h"
#include "../global.h"
#include "vector"

class ParticleManager {
    private:
        std::vector<Particle*> shipParticles;
        std::vector<Particle*> astParticles;
        Ship* ship;
        bool shipIsMoving;
    public:
        ParticleManager(Ship* ship);
        void createShipParticles();
        void drawParticles();
        void createExplosion(int x, int y);
        
        std::vector<Particle*>& getShipParticles();
        std::vector<Particle*>& getAstParticles();
        bool getShipisMoving();
        void setShipIsMoving(bool value);
};
#endif