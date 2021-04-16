#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H
#include "../GameObject/ship.h"
#include "../GameObject/asteroid.h"
#include "vector"

class WaveManager {
    private:
        std::vector<Asteroid*> asteroids;
        Ship* ship;
        float wave;
    public:
        WaveManager(Ship* ship);
        void populateAsteroids();
        void drawWave();
        void prepNextWave();
        void reset();
        void splitAsteroid(int counter, float sinD(float), float cosD(float));
        
        std::vector<Asteroid*>& getAsteroids();
        int getWave();
};

#endif