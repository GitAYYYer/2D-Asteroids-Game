#include "ship.h"
#include "stdio.h"
Ship::Ship() {
    // this->x = ARENA_CENTER_X - ARENA_WIDTH + 50;
    // this->y = ARENA_CENTER_Y - ARENA_HEIGHT + 50;
    this->x = ARENA_CENTER_X;
    this->y = ARENA_CENTER_Y;
    this->currentRotation = -45.0f;
    this->isMovingForward = false;
    this->isRotatingLeft = false;
    this->isRotatingRight = false;
}

void Ship::draw() {
    if (!GAME_OVER) {
        glPushMatrix();
            glTranslatef(this->x, this->y + 5, 0);
            glRotatef(currentRotation, 0, 0, 1);
            glTranslatef(-this->x, -this->y + 5, 0);

            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(PLAYER_FILL_R, PLAYER_FILL_G, PLAYER_FILL_B);
            glVertex2f(this->x + PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot right
            glVertex2f(this->x, this->y - (PLAYER_HEIGHT/2)); // bottom middle
            glVertex2f(this->x, this->y + (PLAYER_HEIGHT/2)); // top middle
            glVertex2f(this->x - PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot left
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(this->x, this->y + 5, 0);
            glRotatef(currentRotation, 0, 0, 1);
            glTranslatef(-this->x, -this->y + 5, 0);

            glBegin(GL_LINE_LOOP);
            glColor3f(PLAYER_OUTLINE_R, PLAYER_OUTLINE_G , PLAYER_OUTLINE_B);
            glVertex2f(this->x, this->y - (PLAYER_HEIGHT/2)); // bottom middle
            glVertex2f(this->x + PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot right
            glVertex2f(this->x, this->y + (PLAYER_HEIGHT/2)); // top middle
            glVertex2f(this->x - PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot left
            glEnd();
        glPopMatrix();
    } else {
        glPushMatrix();
            glTranslatef(this->x, this->y + 5, 0);
            glRotatef(currentRotation++, 0, 0, 1);
            glTranslatef(-this->x, -this->y + 5, 0);

            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(PLAYER_FILL_R, PLAYER_FILL_G, PLAYER_FILL_B);
            glVertex2f(this->x + PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot right
            glVertex2f(this->x, this->y - (PLAYER_HEIGHT/2)); // bottom middle
            glVertex2f(this->x, this->y + (PLAYER_HEIGHT/2)); // top middle
            glVertex2f(this->x - PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot left
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(this->x, this->y + 5, 0);
            glRotatef(currentRotation++, 0, 0, 1);
            glTranslatef(-this->x, -this->y + 5, 0);

            glBegin(GL_LINE_LOOP);
            glColor3f(PLAYER_OUTLINE_R, PLAYER_OUTLINE_G , PLAYER_OUTLINE_B);
            glVertex2f(this->x, this->y - (PLAYER_HEIGHT/2)); // bottom middle
            glVertex2f(this->x + PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot right
            glVertex2f(this->x, this->y + (PLAYER_HEIGHT/2)); // top middle
            glVertex2f(this->x - PLAYER_WIDTH_HALF, this->y - (PLAYER_HEIGHT/2) - PLAYER_DOWN_LENGTH); // bot left
            glEnd();
        glPopMatrix();
    }
}

void Ship::reset() {
    this->x = ARENA_CENTER_X - ARENA_WIDTH + 50;
    this->y = ARENA_CENTER_Y - ARENA_HEIGHT + 50;
    this->currentRotation = -45.0f;
    this->isMovingForward = false;
    this->isRotatingLeft = false;
    this->isRotatingRight = false;
    this->collided = false;
}

float Ship::getX() {
    return x;
}

float Ship::getY() {
    return y;
}

float Ship::getCurrentRotation() {
    return currentRotation;
}

void Ship::setX(float value) {
    x = value;
}

void Ship::setY(float value) {
    y = value;
}

void Ship::setCurrentRotation(float value) {
    currentRotation = value;
}

bool Ship::getIsMovingForward() {
    return isMovingForward;
}

bool Ship::getIsRotatingLeft() {
    return isRotatingLeft;
}

bool Ship::getIsRotatingRight() {
    return isRotatingRight;
}

void Ship::setIsMovingForward(bool value) {
    isMovingForward = value;
}

void Ship::setIsRotatingLeft(bool value) {
    isRotatingLeft = value;
}

void Ship::setIsRotatingRight(bool value) {
    isRotatingRight = value;
}

bool Ship::getCollided() {
    return collided;
}

void Ship::setCollided(bool value) {
    collided = value;
}