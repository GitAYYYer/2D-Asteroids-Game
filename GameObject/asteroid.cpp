#include "asteroid.h"

Asteroid::Asteroid(Ship* ship) {
    int segments = 200;

    // Calculate random float for asteroid speed
    float asteroidRandSpeed = getRandFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);

    // Get a random number between i and segments; that will be the x and y selected for the asteroid.
    int randomNumber = rand() % segments;
    float angle = 2.0f * M_PI * (float(randomNumber) / float(segments));
    float radiusOfOrbit = ORBIT_RADIUS;
    float x = radiusOfOrbit * cosf(angle);
    float y = radiusOfOrbit * sinf(angle);

    this->x = x;
    this->y = y;
    this->spawnX = x;
    this->spawnY = y;
    this->id = rand() % 1000; // DEBUGGING PURPOSES
    this->speed = asteroidRandSpeed;
    this->radius = (rand() % (ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS)) + ASTEROID_MIN_RADIUS;
    this->targetX = ship->getX();
    this->targetY = ship->getY();
    this->currentRotation = 0;
    this->rotateSpeed = getRandFloat(ASTEROID_MIN_ROT_SPEED, ASTEROID_MAX_ROT_SPEED);
    this->rotateDirection = rand() % 2;

    // Get the variations in the asteroid
    int varAmt = rand() % ASTEROID_MAX_VARIATIONS;
    for (int i = 0; i < varAmt; i++) {
        int minStart = floor(ASTEROID_SEGMENTS/varAmt) * i;
        int maxStart = floor(ASTEROID_SEGMENTS/varAmt) * (i + 1);
        int startSegment = (rand() % (maxStart - minStart)) + minStart;
        int endSegment = startSegment + (rand() % 10) + 5;
        int xVariation = getRandFloat(-this->radius/3, this->radius/3);
        int yVariation = getRandFloat(-this->radius/3, this->radius/3);

        AsteroidVariation variation(startSegment, endSegment, xVariation, yVariation);
        variations.push_back(variation);
    }
}

Asteroid::~Asteroid() {

}

void Asteroid::draw() {
    glPushMatrix();
        glRasterPos2f(this->x - 20, this->y - 4);
        char buffer[256];
        sprintf(buffer, "%d", this->id);
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
        }
        
        glTranslatef(this->x, this->y, 0);
        glRotatef(this->currentRotation, 0, 0, 1);
        glTranslatef(-this->x, -this->y, 0);
        glBegin(GL_LINE_LOOP);
        glColor3f(255, 255, 255);
        for(int segCounter = 0; segCounter < ASTEROID_SEGMENTS; segCounter++) {
            float xVariation = 0;
            float yVariation = 0;
            for (int vecCounter = 0; vecCounter < variations.size(); vecCounter++) {
                AsteroidVariation currentVar = variations[vecCounter];
                bool afterMinSegment = segCounter >= currentVar.startSegment;
                bool beforeMaxSegment = segCounter <= currentVar.endSegment;
                if (afterMinSegment && beforeMaxSegment) {
                    xVariation = currentVar.xVariation;
                    yVariation = currentVar.yVariation;
                }
            }

            float angle = 2.0f * M_PI * (float(segCounter) / float(ASTEROID_SEGMENTS));
            float x = (this->radius * cosf(angle)) + xVariation;
            float y = (this->radius * sinf(angle)) + yVariation;

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

float Asteroid::getCurrentRotation() {
    return currentRotation;
}

int Asteroid::getRotateDirection() {
    return rotateDirection;
}

float Asteroid::getRotateSpeed() {
    return rotateSpeed;
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

void Asteroid::setCurrentRotation(float value) {
    currentRotation = value;
}

void Asteroid::setRotateDirection(int value) {
    rotateDirection = value;
}

void Asteroid::setRotateSpeed(float value) {
    rotateSpeed = value;
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

float getRandFloat(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}