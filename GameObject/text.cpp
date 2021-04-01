#include "text.h"

Text::Text(int number, float x, float y) {
    sprintf(this->buffer, "%d", number);
    this->x = x;
    this->y = y;
    this->width = calcWidth(this->buffer);
    this->length = strlen(this->buffer);
}

Text::Text(string text, float x, float y) {
    sprintf(this->buffer, "%s", text.c_str());
    this->x = x;
    this->y = y;
    this->width = calcWidth(this->buffer);
    this->length = strlen(this->buffer);
}

int Text::calcWidth(char buffer[]) {
    int newWidth = 0;
    for (int i = 0; i < this->length; i++) {
        newWidth += glutBitmapWidth(GLUT_BITMAP_8_BY_13, this->buffer[i]);
    }
    return newWidth;
}

void Text::draw() {
    glRasterPos2f(this->x, this->y);
    for (int i = 0; i < this->length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, this->buffer[i]);
    }
}

void Text::updateTimeAlive(int glutTime) {
    int minutes = glutTime/1000/60;
    int seconds = glutTime/1000%60;
    sprintf(this->buffer, "%dm%ds", minutes, seconds);
    this->length = strlen(this->buffer);
    this->width = calcWidth(this->buffer);

    // Give 20 units of 'padding' for timeAlive
    this->x = ORTHO_LEFT + 20;
    this->y = ORTHO_UP - 20;
}

void Text::updateScore(int newScore) {
    sprintf(this->buffer, "%d", newScore);
    this->length = strlen(this->buffer);
    this->width = calcWidth(this->buffer);

    // Give 20 units of 'padding' for score, need to account for score width too.
    this->x = ORTHO_RIGHT - 20 - this->width;
    this->y = ORTHO_UP - 20;
}

void Text::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}

char* Text::getBuffer() {
    return buffer;
}

void Text::setBuffer(int newNumber) {
    sprintf(this->buffer, "%d", newNumber);
    this->length = strlen(this->buffer);
}

void Text::setBuffer(string text) {
    sprintf(this->buffer, "%s", text.c_str());
    this->length = strlen(this->buffer);
}