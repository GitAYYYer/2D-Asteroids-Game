#include "bullet.h"

Bullet::Bullet(Ship* ship) {
    this->x = ship->getX() - (sinf(ship->getCurrentRotation() * M_PI/180) * 40);
    this->y = ship->getY() + (cosf(ship->getCurrentRotation() * M_PI/180) * 40);
    this->speed = BULLET_SPEED;
    this->angle = ship->getCurrentRotation();
    this->size = BULLET_SIZE;
    this->r = BULLET_R;
    this->g = BULLET_G;
    this->b = BULLET_B;
}

Bullet::Bullet(float x, float y, float angle) {
    this->x = x;
    this->y = y;
    this->speed = BULLET_SPEED * 0.75;
    this->angle = angle;
    this->size = BULLET_SIZE;
    this->r = 255;
    this->g = 0;
    this->b = 0;
}

void Bullet::draw() {
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

float Bullet::getX() {
    return x;
}

float Bullet::getY() {
    return y;
}

float Bullet::getSpeed() {
    return speed;
}

float Bullet::getAngle() {
    return angle;
}

int Bullet::getSize() {
    return size;
}

void Bullet::setX(float value) {
    x = value;
}

void Bullet::setY(float value) {
    y = value;
}

void Bullet::setSpeed(float value) {
    speed = value;
}

void Bullet::setAngle(float value) {
    angle = value;
}

void Bullet::setSize(int value) {
    size = value;
}