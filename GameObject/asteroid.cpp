#include "asteroid.h"

Asteroid::Asteroid(Ship* ship) {
    int segments = 200;

    // Calculate random float for asteroid speed
    float asteroidRandSpeed = getRandFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);

    // Get a random number between i and segments; that will be the x and y selected for the asteroid.
    int randomNumber = rand() % segments;
    float angle = 2.0f * M_PI * (float(randomNumber) / float(segments));
    float radiusOfOrbit = ORBIT_RADIUS;
    float x = ARENA_CENTER_X + radiusOfOrbit * cosf(angle);
    float y = ARENA_CENTER_Y + radiusOfOrbit * sinf(angle);

    this->id = rand() % 1000; // DEBUGGING PURPOSES
    this->x = x;
    this->y = y;
    this->spawnX = x;
    this->spawnY = y;
    this->targetX = ship->getX();
    this->targetY = ship->getY();
    // this->x = 600;
    // this->y = 500;
    // this->spawnX = this->x;
    // this->spawnY = this->y;
    // this->targetX = ship->getX();
    // this->targetY = ship->getY();
    this->theta = atan2(this->targetY - this->spawnY, this->targetX - this->spawnX) * 180/M_PI;
    this->speed = asteroidRandSpeed;
    this->radius = (rand() % (ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS)) + ASTEROID_MIN_RADIUS;
    // this->speed = 0.3;
    // this->radius = 40;
    this->hp = (float)this->radius * 2.1;
    this->currentRotation = 0;
    this->rotateSpeed = getRandFloat(ASTEROID_MIN_ROT_SPEED, ASTEROID_MAX_ROT_SPEED);
    this->rotateDirection = rand() % 2;
    this->inArena = false;
    this->horizontalBounce = false;
    this->verticalBounce = false;
    this->asteroidBounce = false;
    this->fromSplit = false;

    printf("Asteroid #%d, Speed: %f, Radius: %d, (x,y): (%f,%f)\n", id, speed, radius, this->x, this->y);

    // Get the variations in the asteroid
    int varAmt = rand() % ASTEROID_MAX_VARIATIONS;
    for (int i = 0; i < varAmt; i++) {
        int minStart = floor(ASTEROID_SEGMENTS/varAmt) * i;
        int maxStart = floor(ASTEROID_SEGMENTS/varAmt) * (i + 1);
        int startSegment = (rand() % (maxStart - minStart)) + minStart;
        int endSegment = startSegment + (rand() % 10) + 5;
        int xVariation = getRandFloat(-this->radius/4, this->radius/4);
        int yVariation = getRandFloat(-this->radius/4, this->radius/4);

        AsteroidVariation variation(startSegment, endSegment, xVariation, yVariation);
        variations.push_back(variation);
    }
}

Asteroid::~Asteroid() {

}

void Asteroid::draw() {
    glPushMatrix();
        // glRasterPos2f(this->x - 20, this->y - 4);
        // char buffer[256];
        // sprintf(buffer, "%d", this->id);
        // int len = strlen(buffer);
        // for (int i = 0; i < len; i++) {
        //     glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
        // }
        
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

float Asteroid::getTheta() {
    return theta;
}

float Asteroid::getHP() {
    return hp;
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

bool Asteroid::getInArena() {
    return inArena;
}

bool Asteroid::getHorizontalBounce() {
    return horizontalBounce;
}

bool Asteroid::getVerticalBounce() {
    return verticalBounce;
}

bool Asteroid::getAsteroidBounce() {
    return asteroidBounce;
}

bool Asteroid::getFromSplit() {
    return fromSplit;
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

void Asteroid::setTheta(float value) {
    theta = value;
}

void Asteroid::setHP(float value) {
    hp = value;
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

void Asteroid::setInArena(bool value) {
    inArena = value;
}

void Asteroid::setHorizontalBounce(bool value) {
    horizontalBounce = value;
}

void Asteroid::setVerticalBounce(bool value) {
    verticalBounce = value;
}

void Asteroid::setAsteroidBounce(bool value) {
    asteroidBounce = value;
}

void Asteroid::setFromSplit(bool value) {
    fromSplit = value;
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

float getRandFloat(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}