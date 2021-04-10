#ifndef BOSS_MANAGER_H
#define BOSS_MANAGER_H
#include "../GameObject/bosses/tentacleMonster.h"
#include "../GameObject/ship.h"
#include "bulletManager.h"
#include "../global.h"
#include "vector"
#include "random"

using std::vector;
using std::get;

class BossManager {
    private:
        Ship* ship;
        TentacleMonster* tm;
        BulletManager* bossBullets;
        bool fightingBoss;

    public:
        BossManager(Ship* ship);
        void performAction();
        void reset();
        void setNewBoss();

        bool getFightingBoss();
        void setFightingBoss(bool value);
        TentacleMonster* getTM();
        BulletManager* getBossBulletManager();
};

#endif