#include "bossMath.h"

float sinDeg(float angle) {
    float radians = (angle * M_PI) / 180;
    return sinf(radians);
}

float cosDeg(float angle) {
    float radians = (angle * M_PI) / 180;
    return cosf(radians);
}

void calcTentacleMonsterMovement(TentacleMonster* tm, float deltaTime) {
    if (!tm->getInArena()) {
        bool horiCheck = tm->getX() + (tm->getHeadWidth() * 3) < ARENA_CENTER_X + ARENA_WIDTH
            && tm->getX() - (tm->getHeadWidth() * 3) > ARENA_CENTER_X - ARENA_WIDTH;
        bool vertiCheck = tm->getY() + (tm->getHeadHeight() * 2) < ARENA_CENTER_Y + ARENA_HEIGHT
            && tm->getY() - (tm->getHeadHeight() * 2) > ARENA_CENTER_Y - ARENA_HEIGHT;
        if (horiCheck && vertiCheck) {
            tm->setInArena(true);
        }
    }

    tm->setX(tm->getX() + deltaTime * tm->getSpeed() * cosDeg(tm->getTheta()));
    tm->setY(tm->getY() + deltaTime * tm->getSpeed() * sinDeg(tm->getTheta()));
}

void calcBossCollision(TentacleMonster* tm, Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets) {
    calcShipCollision(tm, ship);
    calcAstCollision(tm, asteroids);
}

void calcShipCollision(TentacleMonster* tm, Ship* ship) {
    if (ship->getCollided()) {
        GAME_OVER = true;
        ship->setIsMovingForward(false);
        ship->setIsRotatingLeft(false);
        ship->setIsRotatingRight(false);
        return;
    }

    for(int i = 0; i < 200; i++) {
        float angle = 2.0f * M_PI * (float(i) / float(200));
        float shipX = ship->getX() + ((PLAYER_HEIGHT/2) + 5) * cosf(angle);
        float shipY = ship->getY() + ((PLAYER_HEIGHT/2) + 5) * sinf(angle);
        bool xOverlap = shipX > tm->getX() - tm->getHeadWidth() || shipX < tm->getX() + tm->getHeadWidth();
        bool yOverlap = shipY > tm->getY() - tm->getHeadHeight() || shipY < tm->getY() + tm->getHeadHeight();
        if (xOverlap && yOverlap) {
            ship->setCollided(true);
        }
    }
}
