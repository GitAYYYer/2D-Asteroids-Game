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
        int arms, bodySegments;
        bool inArena, armFluct;
        vector< tuple<float, float> > armCoords;
        vector< tuple<float, float> > armEndPtCoords;
        float currentYFluct, endPointFluct;
        float lastShipX, lastShipY;
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
        float getLastShipX();
        float getLastShipY();
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
        void setLastShipX(float value);
        void setLastShipY(float value);

        vector< tuple<float, float> >& getArmCoords();
        vector <tuple<float, float> >& getArmEndPtCoords();
};

float getRanFloat(float min, float max);

#endif