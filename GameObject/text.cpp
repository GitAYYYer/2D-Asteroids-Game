#include "text.h"

Text::Text(int number, float x, float y, void* font) {
    sprintf(this->buffer, "%d", number);
    this->x = x;
    this->y = y;
    this->width = calcWidth(this->buffer);
    this->length = strlen(this->buffer);
    this->font = font;
}

Text::Text(string text, float x, float y, void* font) {
    sprintf(this->buffer, "%s", text.c_str());
    this->x = x;
    this->y = y;
    this->width = calcWidth(this->buffer);
    this->length = strlen(this->buffer);
    this->font = font;
}

int Text::calcWidth(char buffer[]) {
    int newWidth = 0;
    for (int i = 0; i < this->length; i++) {
        newWidth += glutBitmapWidth(this->font, buffer[i]);
    }
    return newWidth;
}

// Not sure what the heights are for anything not 8x13 or 9x15.
int Text::calcHeight() {
    int height;
    if (font == GLUT_BITMAP_8_BY_13) {
        height = 13;
    } else if (font == GLUT_BITMAP_9_BY_15) {
        height = 15;
    } else if (font == GLUT_BITMAP_HELVETICA_10) {
        height = 10;
    } else if (font == GLUT_BITMAP_HELVETICA_12) {
        height = 12;
    } else if (font == GLUT_BITMAP_HELVETICA_18) {
        height = 18;
    } else if (font == GLUT_BITMAP_TIMES_ROMAN_10) {
        height = 10;
    } else if (font == GLUT_BITMAP_TIMES_ROMAN_24) {
        height = 24;
    }
    return height;
}

void Text::draw() {
    glRasterPos2f(this->x, this->y);
    for (int i = 0; i < this->length; i++) {
        glutBitmapCharacter(this->font, this->buffer[i]);
    }
}

void Text::updateTimeAlive(int glutTime) {
    int minutes = glutTime/1000/60;
    int seconds = glutTime/1000%60;
    sprintf(this->buffer, "%dm%ds", minutes, seconds);
    this->length = strlen(this->buffer);
    this->width = calcWidth(this->buffer);

    // Give % padding for timeAlive, % being based on the ORTHO sizes
    this->x = ORTHO_LEFT + (ORTHO_RIGHT*0.05);
    this->y = ORTHO_UP - (ORTHO_UP*0.05);
}

void Text::updateScore(int newScore) {
    sprintf(this->buffer, "%d", newScore);
    this->length = strlen(this->buffer);
    this->width = calcWidth(this->buffer);

    // Give padding for score, need to account for score width too.
    this->x = ORTHO_RIGHT - (ORTHO_RIGHT*0.04) - this->width;
    this->y = ORTHO_UP - (ORTHO_UP*0.04);
}

// x and y args here are the center point of where the text should be drawn.
// i.e. calc width and put h
void Text::setPos(float x, float y) {
    this->x = x - (this->calcWidth(buffer)/2);
    this->y = y - (this->calcHeight()/2);
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