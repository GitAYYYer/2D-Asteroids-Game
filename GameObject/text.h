#ifndef TEXT_H
#define TEXT_H
#include "../global.h"
#include "stdio.h"
#include "string"
#include "cstring"
#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;

class Text {
    private:
        // 'buffer' here is the actual text to be displayed.
        char buffer[256];
        float x, y;
        int width, length;
        void* font;
    public:
        Text(int number, float x, float y, void* font);
        Text(string text, float x, float y, void* font);
        int calcWidth(char buffer[]);
        int calcHeight();
        void draw();
        void updateTimeAlive(int glutTime);
        void updateScore(int newScore);

        void setPos(float x, float y);
        char* getBuffer();
        void setBuffer(int newNumber);
        void setBuffer(string text);
};

#endif