#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H
#include "../GameObject/bullet.h"
#include "../global.h"
#include "vector"

class BulletManager {
    private:
        std::vector<Bullet*> bullets;
        Ship* ship;
        bool shipIsShooting;
        int lastBulletTimer;
    public:
        BulletManager(Ship* ship);
        void createBullets();
        void drawBullets();
        std::vector<Bullet*>& getBullets();

        bool getShipIsShooting();
        int getLastBulletTimer();
        void setShipIsShooting(bool value);
        void setLastBulletTimer(int value);
};

#endif