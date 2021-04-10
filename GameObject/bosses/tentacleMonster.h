#ifndef TENTACLE_MONSTER_H
#define TENTACLE_MONSTER_H
#include "../../global.h"
#include "random"
#include "tuple"
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

using std::vector;
using std::tuple;
using std::get;

class TentacleMonster {
    private:
        float x, y, speed, theta, hp;
        int xRadius, yRadius, headHeight, headWidth;
        int arms, armSegments, bodySegments;
        bool inArena, armFluct;
        vector< tuple<float, float> > armCoords;
        float currentYFluct, endPointFluct;
    public:
        TentacleMonster();
        void drawHead();
        void drawBody();
        void drawEyes();
        void drawArm(float xStart, float yStart, int armNumber);
        void drawArms();
        void draw();
        void changeArmFluct();

        float getX();
        float getY();
        int getXRadius();
        int getYRadius();
        int getHeadHeight();
        int getHeadWidth();
        float getSpeed();
        float getTheta();
        float getHp();
        bool getInArena();
        void setX(float value);
        void setY(float value);
        void setXRadius(int value);
        void setYRadius(int value);
        void setHeadHeight(int value);
        void setHeadWidth(int value);
        void setSpeed(float value);
        void setTheta(float value);
        void setHp(float value);
        void setInArena(bool value);

        vector< tuple<float, float> >& getArmCoords();
};

float getRanFloat(float min, float max);

#endif