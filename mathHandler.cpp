#include "mathHandler.h"

float sinD(float angle) {
    float radians = (angle * M_PI) / 180;
    return sinf(radians);
}

float cosD(float angle) {
    float radians = (angle * M_PI) / 180;
    return cosf(radians);
}

void calcShipMovement(Ship* ship, float deltaTime) {
    if (ship->getIsMovingForward()) {
        ship->setX(ship->getX() - deltaTime * SHIP_MOVEMENT_SPEED * sinD(ship->getCurrentRotation()));
        ship->setY(ship->getY() + deltaTime * SHIP_MOVEMENT_SPEED * cosD(ship->getCurrentRotation()));
    }
    if (ship->getIsRotatingLeft()) {
        ship->setCurrentRotation(ship->getCurrentRotation() + deltaTime * SHIP_ROTATION_SPEED);
    } else if (ship->getIsRotatingRight()) {
        ship->setCurrentRotation(ship->getCurrentRotation() - deltaTime * SHIP_ROTATION_SPEED);
    }
}

void calcAstMovements(vector<Asteroid*>& asteroids, float deltaTime) {
    srand(time(NULL));
    for (int i = 0; i < asteroids.size(); i++) {
        float theta = asteroids[i]->getTheta();
        float xTranslation = asteroids[i]->getSpeed() * deltaTime * cosD(theta);
        float yTranslation = asteroids[i]->getSpeed() * deltaTime * sinD(theta);
        if (asteroids[i]->getAsteroidBounce() && asteroids[i]->getInArena()) {
            xTranslation = -xTranslation;
            yTranslation = -yTranslation;
        }
        if (asteroids[i]->getVerticalBounce()) {
            xTranslation = -xTranslation;
        }
        if (asteroids[i]->getHorizontalBounce()) {
            yTranslation = -yTranslation;
        }

        asteroids[i]->setX(asteroids[i]->getX() + xTranslation);
        asteroids[i]->setY(asteroids[i]->getY() + yTranslation);
        
        if (asteroids[i]->getRotateDirection() == COUNTER_CLOCKWISE) {
            asteroids[i]->setCurrentRotation(asteroids[i]->getCurrentRotation() + deltaTime * asteroids[i]->getRotateSpeed());
        } else {
            asteroids[i]->setCurrentRotation(asteroids[i]->getCurrentRotation() - deltaTime * asteroids[i]->getRotateSpeed());
        }
        
    }
    checkAstDeletion(asteroids);
}

void calcBulletMovements(vector<Bullet*>& bullets, float deltaTime) {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->setX(bullets[i]->getX() - (sinD(bullets[i]->getAngle()) * deltaTime * BULLET_SPEED));
        bullets[i]->setY(bullets[i]->getY() + (cosD(bullets[i]->getAngle()) * deltaTime * BULLET_SPEED));
    }
}

void calcPartMovements(vector<Particle*>& particles, float deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->setX(particles[i]->getX() + (sinD(particles[i]->getAngle()) * deltaTime/10));
        particles[i]->setY(particles[i]->getY() - (cosD(particles[i]->getAngle()) * deltaTime/10));
    }
    checkPartDeletion(particles);
}

void checkCollisions(Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets) {
    if (ship->getCollided()) {
        GAME_OVER = true;
        ship->setIsMovingForward(false);
        ship->setIsRotatingLeft(false);
        ship->setIsRotatingRight(false);
        return;
    }

    // Arena with Ship Collision checks
    checkArenaShipCollision(ship);

    // Arena with Bullet Collision checks, same order as Arena with Ship
    checkArenaBulletCollision(ship, bullets);

    // Asteroid Collision checks with Ship, Bullets and Arena  walls.
    // Get distance between Asteroid x,y and Ship x,y and if the distance is less than Ast radius, collided.
    // Similar with bullet, if distance of bullet to asteroid is less than Ast radius, collided.
    checkAsteroidCollisions(ship, asteroids, bullets);
}

void checkArenaShipCollision(Ship* ship) {
    for(int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float shipX = ship->getX() + (PLAYER_HEIGHT/2) * cosf(theta);
        float shipY = ship->getY() + (PLAYER_HEIGHT/2) * sinf(theta);

        // right wall
        if (shipX > ARENA_CENTER_X + ARENA_WIDTH) {
            ship->setCollided(true);
        // left wall
        } else if (shipX < ARENA_CENTER_X - ARENA_WIDTH) {
            ship->setCollided(true);
        // top wall
        } else if (shipY > ARENA_CENTER_Y + ARENA_HEIGHT) {
            ship->setCollided(true);
        // bottom wall
        } else if (shipY < ARENA_CENTER_Y - ARENA_HEIGHT) {
            ship->setCollided(true);
        }
    }
}

void checkArenaBulletCollision(Ship* ship, vector<Bullet*>& bullets) {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getX() > ARENA_CENTER_X + ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getX() < ARENA_CENTER_X - ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getY() > ARENA_CENTER_Y + ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getY() < ARENA_CENTER_Y - ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void checkAsteroidCollisions(Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets) {
    for (int astCounter = 0; astCounter < asteroids.size(); astCounter++) {
        // Create bounding circle around ship to check collision with asteroid
        // for(int i = 0; i < 100; i++) {
        //     float theta = 2.0f * M_PI * float(i) / float(100);
        //     float shipX = ship->getX() + (PLAYER_HEIGHT/2) * cosf(theta);
        //     float shipY = ship->getY() + (PLAYER_HEIGHT/2) * sinf(theta);

        //     float astShipDistance = sqrt(pow(shipX - asteroids[astCounter]->getX(), 2) + pow(shipY - asteroids[astCounter]->getY(), 2));
        //     if (astShipDistance < asteroids[astCounter]->getRadius()) {
        //         ship->setCollided(true);
        //     }
        // }

        // Check bullet's collision with asteroid
        for (int bullCounter = 0; bullCounter < bullets.size(); bullCounter++) {
            float bullX = bullets[bullCounter]->getX();
            float bullY = bullets[bullCounter]->getY();
            float astBullDistance = sqrt(pow(bullX - asteroids[astCounter]->getX(), 2) + pow(bullY - asteroids[astCounter]->getY(), 2));
            if (astBullDistance < asteroids[astCounter]->getRadius()) {
                delete bullets[bullCounter];
                bullets.erase(bullets.begin() + bullCounter);

                if (asteroids[astCounter]->getHP() - BULLET_DMG <= 0) {
                    delete asteroids[astCounter];
                    asteroids.erase(asteroids.begin() + astCounter);
                    SCORE += 1;
                } else {
                    asteroids[astCounter]->setHP(asteroids[astCounter]->getHP() - BULLET_DMG);
                }
            }
        }

        // Check if two asteroids in the vector have collided (distance < sum of two radii)
        for (int j = astCounter + 1; j < asteroids.size(); j++) {
            float distance = sqrt(pow(asteroids[astCounter]->getX() - asteroids[j]->getX(), 2) + pow(asteroids[astCounter]->getY() - asteroids[j]->getY(), 2));
            if (distance < asteroids[astCounter]->getRadius() + asteroids[j]->getRadius()) {
                asteroids[astCounter]->setAsteroidBounce(!asteroids[astCounter]->getAsteroidBounce());
                asteroids[j]->setAsteroidBounce(!asteroids[j]->getAsteroidBounce());
            }
        }

        // Check if Asteroid is within Arena, and then after if the asteroid has collided with one of the walls.
        // Note: dist + radius because dist is from origin to center of asteroid, then add on the extra radius.
        bool astInArenaWidth = asteroids[astCounter]->getX() + asteroids[astCounter]->getRadius() < ARENA_CENTER_X + ARENA_WIDTH
                            && asteroids[astCounter]->getX() - asteroids[astCounter]->getRadius() > ARENA_CENTER_X - ARENA_WIDTH;
        bool astInArenaHeight = asteroids[astCounter]->getY() + asteroids[astCounter]->getRadius() < ARENA_CENTER_Y + ARENA_HEIGHT
                            && asteroids[astCounter]->getY() - asteroids[astCounter]->getRadius() > ARENA_CENTER_Y - ARENA_HEIGHT;
        
        if (astInArenaWidth && astInArenaHeight && !asteroids[astCounter]->getInArena()) {
            asteroids[astCounter]->setInArena(true);
        }

        if (asteroids[astCounter]->getInArena()) {
            float x = asteroids[astCounter]->getX();
            float y = asteroids[astCounter]->getY();
            int astRadius = asteroids[astCounter]->getRadius();
            // right wall, left wall, top wall, bottom wall
            // dont need to form circle because the point of collision with each wall will be 1 of 4 points on the asteroid
            // if (asteroids[astCounter]->getX() + astRadius >= ARENA_CENTER_X + ARENA_WIDTH) {
            //     asteroids[astCounter]->setVerticalBounce(!asteroids[astCounter]->getVerticalBounce());
            // } else if (asteroids[astCounter]->getX() - astRadius <= ARENA_CENTER_X - ARENA_WIDTH) {
            //     asteroids[astCounter]->setVerticalBounce(!asteroids[astCounter]->getVerticalBounce());
            // } else if (asteroids[astCounter]->getY() + astRadius >= ARENA_CENTER_Y + ARENA_HEIGHT) {
            //     asteroids[astCounter]->setHorizontalBounce(!asteroids[astCounter]->getHorizontalBounce());
            // } else if (asteroids[astCounter]->getY() - astRadius <= ARENA_CENTER_Y - ARENA_HEIGHT) {
            //     asteroids[astCounter]->setHorizontalBounce(!asteroids[astCounter]->getHorizontalBounce());
            // }
            float rightWallDist = sqrt(pow((ARENA_CENTER_X + ARENA_WIDTH) - x, 2));
            float leftWallDist = sqrt(pow((ARENA_CENTER_X - ARENA_WIDTH) - x, 2));
            float topWallDist = sqrt(pow((ARENA_CENTER_Y + ARENA_HEIGHT) - y, 2));
            float botWallDist = sqrt(pow((ARENA_CENTER_Y - ARENA_HEIGHT) - y, 2));

            if (rightWallDist < astRadius) {
                asteroids[astCounter]->setVerticalBounce(!asteroids[astCounter]->getVerticalBounce());
            } else if (leftWallDist < astRadius) {
                asteroids[astCounter]->setVerticalBounce(!asteroids[astCounter]->getVerticalBounce());
            } else if (topWallDist < astRadius) {
                asteroids[astCounter]->setHorizontalBounce(!asteroids[astCounter]->getHorizontalBounce());
            } else if (botWallDist < astRadius) {
                asteroids[astCounter]->setHorizontalBounce(!asteroids[astCounter]->getHorizontalBounce());
            }
        }
    }
}

// Delete asteroid if its distance from center of arena is greater than the orbit radius.
void checkAstDeletion(vector<Asteroid*>& asteroids) {
    for (int i = 0; i < asteroids.size(); i++) {
        float distance = sqrt(pow(ARENA_CENTER_X - asteroids[i]->getX(), 2) + pow(ARENA_CENTER_Y - asteroids[i]->getY(), 2));
        if (distance > ORBIT_RADIUS) {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void checkPartDeletion(vector<Particle*>& particles) {
    for (int i = 0; i < particles.size(); i++) {
        if (glutGet(GLUT_ELAPSED_TIME) - particles[i]->getSizeTimer() >= PARTICLE_DECAY_MS) {
            particles[i]->setSize(particles[i]->getSize() - 1);
            particles[i]->setSizeTimer(glutGet(GLUT_ELAPSED_TIME));
        }
        if (particles[i]->getSize() == 0) {
            delete particles[i];
            particles.erase(particles.begin() + i);
        }
    }
}