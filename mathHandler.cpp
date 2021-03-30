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

void calcAstMovements(std::vector<Asteroid*>& asteroids, float deltaTime) {
    srand(time(NULL));
    for (int i = 0; i < asteroids.size(); i++) {
        float delta_x = asteroids[i]->getSpawnX() - asteroids[i]->getTargetX();
        float delta_y = asteroids[i]->getSpawnY() - asteroids[i]->getTargetY();
        float theta = atan2(delta_y, delta_x)*180/M_PI;

        asteroids[i]->setX(asteroids[i]->getX() - (asteroids[i]->getSpeed() * deltaTime * cosD(theta)));
        asteroids[i]->setY(asteroids[i]->getY() - (asteroids[i]->getSpeed() * deltaTime * sinD(theta)));
        
        if (asteroids[i]->getRotateDirection() == 0) {
            asteroids[i]->setCurrentRotation(asteroids[i]->getCurrentRotation() + deltaTime * asteroids[i]->getRotateSpeed());
        } else {
            asteroids[i]->setCurrentRotation(asteroids[i]->getCurrentRotation() - deltaTime * asteroids[i]->getRotateSpeed());
        }
        
    }
    checkAstDeletion(asteroids);
}

void calcBulletMovements(std::vector<Bullet*>& bullets, float deltaTime) {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->setX(bullets[i]->getX() - (sinD(bullets[i]->getAngle()) * deltaTime * BULLET_SPEED));
        bullets[i]->setY(bullets[i]->getY() + (cosD(bullets[i]->getAngle()) * deltaTime * BULLET_SPEED));
    }
}

void calcPartMovements(std::vector<Particle*>& particles, float deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->setX(particles[i]->getX() + (sinD(particles[i]->getAngle()) * deltaTime/10));
        particles[i]->setY(particles[i]->getY() - (cosD(particles[i]->getAngle()) * deltaTime/10));
    }
    checkPartDeletion(particles);
}

void checkCollisions(Ship* ship, std::vector<Asteroid*> asteroids, std::vector<Bullet*>& bullets) {
    if (ship->getCollided()) {
        GAME_OVER = true;
        ship->setIsMovingForward(false);
        ship->setIsRotatingLeft(false);
        ship->setIsRotatingRight(false);
        return;
    }

    // Arena with Ship Collision checks
    // right wall
    if (ship->getX() + (PLAYER_HEIGHT/2) > ARENA_WIDTH) {
        ship->setCollided(true);
    // left wall
    } else if (ship->getX() - (PLAYER_HEIGHT/2) < -ARENA_WIDTH) {
        ship->setCollided(true);
    // top wall
    } else if (ship->getY() + (PLAYER_HEIGHT/2) > ARENA_HEIGHT) {
        ship->setCollided(true);
    // bottom wall
    } else if (ship->getY() - (PLAYER_HEIGHT/2) < -ARENA_HEIGHT - 15) {
        ship->setCollided(true);
    }

    // Arena with Bullet Collision checks, same order as Arena with Ship
    checkBulletDeletion(bullets);

    // Asteroid with Ship Collision check
    // Get distance between Asteroid x,y and Ship x,y and if the distance is less than Ast radius, collided.
    for (int astCounter = 0; astCounter < asteroids.size(); astCounter++) {
        for(int i = 0; i < 100; i++) {
            float theta = 2.0f * M_PI * float(i) / float(100);
            float shipX = ship->getX() + (PLAYER_HEIGHT - 20) * cosf(theta);
            float shipY = ship->getY() + (PLAYER_HEIGHT - 20) * sinf(theta);

            float distance = sqrt(pow(shipX - asteroids[astCounter]->getX(), 2) + pow(shipY - asteroids[astCounter]->getY(), 2));
            if (distance < asteroids[astCounter]->getRadius()) {
                printf("Collided: #%d with Speed: %f\n", asteroids[astCounter]->id, asteroids[astCounter]->getSpeed());
                ship->setCollided(true);
            }
        }
    }
}

// Delete asteroid if its distance from origin is greater than the orbit radius.
void checkAstDeletion(std::vector<Asteroid*>& asteroids) {
    for (int i = 0; i < asteroids.size(); i++) {
        float distance = sqrt(pow(asteroids[i]->getX(), 2) + pow(asteroids[i]->getY(), 2));
        if (distance > ORBIT_RADIUS) {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void checkBulletDeletion(std::vector<Bullet*>& bullets) {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getX() > ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getX() < -ARENA_WIDTH) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getY() > ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else if (bullets[i]->getY() < -ARENA_HEIGHT) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void checkPartDeletion(std::vector<Particle*>& particles) {
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