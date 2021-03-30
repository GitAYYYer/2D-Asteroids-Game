#include "asteroidVariation.h"

AsteroidVariation::AsteroidVariation(int start, int end, int x, int y) {
    this->startSegment = start;
    this->endSegment = end;
    this->xVariation = x;
    this->yVariation = y;
}