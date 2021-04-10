#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H
#include "../GameObject/bullet.h"
#include "../GameObject/bosses/tentacleMonster.h"
#include "../global.h"
#include "vector"

class BulletManager {
    private:
        std::vector<Bullet*> bullets;
        Ship* ship;
        TentacleMonster* tm;
        bool shipIsShooting;
        int lastBulletTimer;
    public:
        BulletManager(Ship* ship);
        BulletManager(TentacleMonster* tm);
        void createBullets();
        void createBossBullets(float x, float y, float angle);
        void drawBullets();
        void reset();

        std::vector<Bullet*>& getBullets();
        bool getShipIsShooting();
        int getLastBulletTimer();
        void setShipIsShooting(bool value);
        void setLastBulletTimer(int value);
};

#endif