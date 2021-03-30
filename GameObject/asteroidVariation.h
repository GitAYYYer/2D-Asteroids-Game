#ifndef ASTEROID_VARIATION_H
#define ASTEROID_VARIATION_H

// Class is used to simplify how I store variations per asteroid.
class AsteroidVariation {
    public:
        AsteroidVariation(int start, int end, int x, int y);
        int startSegment;
        int endSegment;
        int xVariation;
        int yVariation;
};

#endif