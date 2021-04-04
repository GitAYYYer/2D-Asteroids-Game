#include "particle.h"

Particle::Particle(Ship* ship) {
    int randomAngleOffset = (rand() % PARTICLE_MAX_ANGLE_OFFSET - PARTICLE_MIN_ANGLE_OFFSET) + PARTICLE_MIN_ANGLE_OFFSET;
    this->angle = ship->getCurrentRotation() + randomAngleOffset;
    this->x = ship->getX() + (sinf(ship->getCurrentRotation() * M_PI/180) * 40);
    this->y = ship->getY() - (cosf(ship->getCurrentRotation() * M_PI/180) * 40);
    this->size = PARTICLE_START_SIZE;
    this->sizeTimer = glutGet(GLUT_ELAPSED_TIME);

    do {
        this->r = rand() % 255;
        this->g = rand() % 255;
        this->b = rand() % 255;
    } while (this->r + this->g + this->b <= 255);
}

Particle::Particle(int x, int y, int speed, float angle) {
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->size = EXPLO_PARTICLE_START_SIZE;
    this->sizeTimer = glutGet(GLUT_ELAPSED_TIME);
    do {
        this->r = rand() % 255;
        this->g = rand() % 255;
        this->b = rand() % 255;
    } while (this->r + this->g + this->b <= 255);
}

void Particle::draw() {
    glPushMatrix();
        glPointSize(this->size);
        glTranslatef(this->x, this->y, 0);
        glRotatef(this->angle, 0, 0, 1);
        glTranslatef(-this->x, -this->y, 0);

        glBegin(GL_POINTS);
        glColor3ub(this->r, this->g, this->b);
        glVertex2f(this->x, this->y);
        glEnd();
    glPopMatrix();
}

float Particle::getX() {
    return x;
}

float Particle::getY() {
    return y;
}

float Particle::getSize() {
    return size;
}

float Particle::getAngle() {
    return angle;
}

int Particle::getSizeTimer() {
    return sizeTimer;
}

void Particle::setX(float value) {
    x = value;
}

void Particle::setY(float value) {
    y = value;
}

void Particle::setSize(float value) {
    size = value;
}

void Particle::setAngle(float value) {
    angle = value;
}

void Particle::setSizeTimer(int value) {
    sizeTimer = value;
}

void Particle::setRGB(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}