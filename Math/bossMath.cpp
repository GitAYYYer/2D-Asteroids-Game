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
            tm->setSpeed(0);
        }
    }

    tm->setX(tm->getX() + deltaTime * tm->getSpeed() * cosDeg(tm->getTheta()));
    tm->setY(tm->getY() + deltaTime * tm->getSpeed() * sinDeg(tm->getTheta()));
}

void calcBossBulletMovement(vector<Bullet*>& bullets, float deltaTime) {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->setX(bullets[i]->getX() - (sinDeg(bullets[i]->getAngle()) * deltaTime * bullets[i]->getSpeed()));
        bullets[i]->setY(bullets[i]->getY() + (cosDeg(bullets[i]->getAngle()) * deltaTime * bullets[i]->getSpeed()));
    }
}

void calcBossCollision(BossManager* bm, Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets, ParticleManager* particleManager) {
    calcShipCollision(bm->getTM(), ship);
    calcAstCollision(bm->getTM(), asteroids, particleManager);
    calcBullCollision(bm->getTM(), bullets);
}

void calcShipCollision(TentacleMonster* tm, Ship* ship) {
    if (ship->getCollided() && !GOD_MODE) {
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
        bool xOverlap = shipX > tm->getX() - tm->getHeadWidth() - 80 && shipX < tm->getX() + tm->getHeadWidth();
        bool yOverlap = shipY > tm->getY() - tm->getHeadHeight() + 30 && shipY < tm->getY() + tm->getHeadHeight();
        if (xOverlap && yOverlap) {
            ship->setCollided(true);
        }
    }
}

void calcAstCollision(TentacleMonster* tm, vector<Asteroid*>& asteroids, ParticleManager* particleManager) {
    for (int i = 0; i < asteroids.size(); i++) {
        float astX = asteroids[i]->getX();
        float astY = asteroids[i]->getY();
        int radius = asteroids[i]->getRadius();
        bool xOverlap = astX - radius < tm->getX() + tm->getHeadWidth() && astX + radius > tm->getX() - tm->getHeadWidth();
        bool yOverlap = astY + radius > tm->getY() - tm->getHeadHeight() + 30 && astY - radius < tm->getY() + tm->getHeadHeight();
        if (xOverlap && yOverlap) {
            particleManager->createExplosion(asteroids[i]->getX(), asteroids[i]->getY());
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void calcBullCollision(TentacleMonster* tm, vector<Bullet*>& bullets) {
    for (int i = 0; i < bullets.size(); i++) {
        float bullX = bullets[i]->getX();
        float bullY = bullets[i]->getY();
        bool xOverlap = bullX < tm->getX() + tm->getHeadWidth() && bullX > tm->getX() - tm->getHeadWidth();
        bool yOverlap = bullY > tm->getY() - tm->getHeadHeight() + 30 && bullY < tm->getY() + tm->getHeadHeight();
        if (xOverlap && yOverlap) {
            tm->setHp(tm->getHp() - BULLET_DMG);
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void calcBossBulletsCollision(Ship* ship, BlackHole* blackHole, vector<Bullet*>& bullets) {
    // Check if bullet collides with ship, then check if it collides with arena
    for (int i = 0; i < bullets.size(); i++) {
        float bullX = bullets[i]->getX();
        float bullY = bullets[i]->getY();
        float bullShipDist = pow(bullY - ship->getY(), 2) + pow(bullX - ship->getX(), 2);
        if (bullShipDist < pow((PLAYER_HEIGHT/2) + 5, 2)) {
            ship->setCollided(true);
        }

        if (bullX > ARENA_CENTER_X + ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullX < ARENA_CENTER_X - ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullY > ARENA_CENTER_Y + ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullY < ARENA_CENTER_Y - ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    calcBlackHoleBulletPull(blackHole, bullets);
}

float getPullPower(float distance) {
    float diff = BLACKHOLE_PULL_DISTANCE - distance;
    float multiplier = ceil(diff / BLACKHOLE_PULL_INTERVALS);
    return multiplier * BLACKHOLE_MIN_PULL_POWER;
}

void calcBlackHoleBulletPull(BlackHole* blackHole, vector<Bullet*>& bullets) {
    for (int i = 0; i < bullets.size(); i++) {
        float bhBullDist = pow(blackHole->getX() - bullets[i]->getX(), 2) + pow(blackHole->getY() - bullets[i]->getY(), 2);
        if (bhBullDist <= pow(blackHole->getStartingRadius(), 2)) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
        if (bhBullDist < pow(BLACKHOLE_PULL_DISTANCE, 2)) {
            float angle = (atan2(blackHole->getY() - bullets[i]->getY(), blackHole->getX() - bullets[i]->getX()) - 90) * 180/M_PI;
            float pullPower = getPullPower(sqrt(bhBullDist));
            bullets[i]->setX(bullets[i]->getX() - pullPower * BLACKHOLE_BULLET_PULL_MULTIPLIER * sinDeg(angle));
            bullets[i]->setY(bullets[i]->getY() + pullPower * BLACKHOLE_BULLET_PULL_MULTIPLIER * cosDeg(angle));
        }
    }
}