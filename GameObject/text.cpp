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
    return 0;
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
}

void Text::setBuffer(int newNumber) {
    sprintf(this->buffer, "%d", newNumber);
    this->length = strlen(this->buffer);
}

void Text::setBuffer(string text) {
    sprintf(this->buffer, "%s", text.c_str());
    this->length = strlen(this->buffer);
}