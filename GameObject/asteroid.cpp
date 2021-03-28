#include "asteroid.h"

Asteroid::Asteroid(Ship* ship) {
    int segments = 200;

    // Calculate random float for asteroid speed
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED;
    float r = random * diff;
    float asteroidRandSpeed = ASTEROID_MIN_SPEED + r;

    // Get a random number between i and segments; that will be the x and y selected for the asteroid.
    int randomNumber = rand() % segments;
    float angle = 2.0f * M_PI * (float(randomNumber) / float(segments));
    float radiusOfOrbit = ORBIT_RADIUS;
    // x and y here represent a random coordinate on the orbit that goes around the arena.
    // float x = radiusOfOrbit * cosD(angle * 180);
    // float y = radiusOfOrbit * sinD(angle * 180);
    float x = radiusOfOrbit * cosf(angle);
    float y = radiusOfOrbit * sinf(angle);

    this->x = x;
    this->y = y;
    this->spawnX = x;
    this->spawnY = y;
    this->id = rand() % 1000;
    this->speed = asteroidRandSpeed;
    this->radius = (rand() % (ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS)) + ASTEROID_MIN_RADIUS;
    this->targetX = ship->getX();
    this->targetY = ship->getY();
}

Asteroid::~Asteroid() {

}

void Asteroid::draw() {
    int segments = 200;
    glPushMatrix();
        glRasterPos2f(this->x - 20, this->y - 4);
        char buffer[256];
        sprintf(buffer, "%d", this->id);
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
        }
        
        glBegin(GL_LINE_LOOP);
        glColor3f(255, 255, 255);
        for(int i = 0; i < segments; i++) {
            float angle = 2.0f * M_PI * (float(i) / float(segments));
            // x and y here represent the literal coordinates for the asteroid circumference
            // float x = this->radius * cosD(angle * 180);
            // float y = this->radius * sinD(angle * 180);
            float x = this->radius * cosf(angle);
            float y = this->radius * sinf(angle);

            glVertex2f(x + this->x, y + this->y);
        }
        glEnd();
    glPopMatrix();
}

float Asteroid::getX() {
    return x;
}

float Asteroid::getY() {
    return y;
}

float Asteroid::getSpawnX() {
    return spawnX;
}

float Asteroid::getSpawnY() {
    return spawnY;
}

float Asteroid::getSpeed() {
    return speed;
}

int Asteroid::getRadius() {
    return radius;
}

void Asteroid::setX(float value) {
    x = value;
}

void Asteroid::setY(float value) {
    y = value;
}

void Asteroid::setSpawnX(float value) {
    spawnX = value;
}

void Asteroid::setSpawnY(float value) {
    spawnY = value;
}

void Asteroid::setSpeed(float value) {
    speed = value;
}

void Asteroid::setRadius(int value) {
    radius = value;
}

float Asteroid::getTargetX() {
    return targetX;
}

float Asteroid::getTargetY() {
    return targetY;
}

void Asteroid::setTargetX(float value) {
    targetX = value;
}

void Asteroid::setTargetY(float value) {
    targetY = value;
}

void Asteroid::toString(int astNumber) {
    printf("Asteroid #%d:\n - Pos: (%f, %f)\n - Speed: %f\n - Radius: %d\n", astNumber, x, y, speed, radius);
}