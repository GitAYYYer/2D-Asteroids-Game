#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H
#include "../GameObject/ship.h"
#include "../GameObject/asteroid.h"
#include "vector"

class WaveManager {
    private:
        std::vector<Asteroid*> asteroids;
        Ship* ship;
    public:
        int wave;
        WaveManager(Ship* ship);
        void populateAsteroids();
        void drawWave();
        void prepNextWave();
        std::vector<Asteroid*>& getAsteroids();
};

#endif