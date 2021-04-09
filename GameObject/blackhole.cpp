#include "blackhole.h"

BlackHole::BlackHole() {
    srand(time(NULL));
    this->startingRadius = (rand() % (BLACKHOLE_MAX_RADIUS - BLACKHOLE_MIN_RADIUS)) + BLACKHOLE_MIN_RADIUS;
    this->currentRadius = this->startingRadius;
    // Game starts ship at bottom left of quadrant, so spawn asteroid anywhere other than there
    this->x = getRandomFloat(0, ARENA_CENTER_X + ARENA_WIDTH - this->startingRadius);
    this->y = getRandomFloat(0, ARENA_CENTER_Y + ARENA_HEIGHT - this->startingRadius);
    this->lastPulse = 0;
}

// Draw two circles: One for the outer (To show player the radius) and other is the pulsing circle
void BlackHole::draw() {
    glBegin(GL_LINE_LOOP);
    glColor3f(BLACKHOLE_R, BLACKHOLE_G, BLACKHOLE_B);
    for(int segCounter = 0; segCounter < 100; segCounter++) {
        float angle = 2.0f * M_PI * (float(segCounter) / float(ASTEROID_SEGMENTS));
        float x = this->startingRadius * cosf(angle);
        float y = this->startingRadius * sinf(angle);
        glVertex2f(x + this->x, y + this->y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(BLACKHOLE_R, BLACKHOLE_G, BLACKHOLE_B);
    for(int segCounter = 0; segCounter < 100; segCounter++) {
        float angle = 2.0f * M_PI * (float(segCounter) / float(ASTEROID_SEGMENTS));
        float x = this->currentRadius * cosf(angle);
        float y = this->currentRadius * sinf(angle);
        glVertex2f(x + this->x, y + this->y);
    }
    glEnd();
}

void BlackHole::reset() {

}

float BlackHole::getX() {
    return x;
}

float BlackHole::getY() {
    return y;
}

int BlackHole::getStartingRadius() {
    return startingRadius;
}

int BlackHole::getCurrentRadius() {
    return currentRadius;
}

int BlackHole::getLastPulse() {
    return lastPulse;
}

void BlackHole::setX(float value) {
    x = value;
}

void BlackHole::setY(float value) {
    y = value;
}

void BlackHole::setStartingRadius(int value) {
    startingRadius = value;
}

void BlackHole::setCurrentRadius(int value) {
    currentRadius = value;
}

void BlackHole::setLastPulse(int value) {
    lastPulse = value;
}

float getRandomFloat(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}