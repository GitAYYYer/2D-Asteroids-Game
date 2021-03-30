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
    public:
        Text(int number, float x, float y);
        Text(string text, float x, float y);
        int calcWidth(char buffer[]);
        void draw();
        void updateTimeAlive(int glutTime);

        void setBuffer(int newNumber);
        void setBuffer(string text);

};

#endif