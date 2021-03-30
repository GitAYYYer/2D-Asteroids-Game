#ifndef MATHHANDLER_H
#define MATHHANDLER_H
#include "GameObject/ship.h"
#include "GameObject/asteroid.h"
#include "GameObject/bullet.h"
#include "GameObject/particle.h"
#include <stdio.h>
#include <math.h>
#include <random>
#include <vector>

// Angle should be given in degrees
float sinD(float angle);
// Angle should be given in degrees
float cosD(float angle);

// Calculate Ship X/Y translations
void calcShipMovement(Ship* ship, float deltaTime);

// Calculate Asteroid X/Y translations
void calcAstMovements(std::vector<Asteroid*>& asteroids, float deltaTime);

void calcBulletMovements(std::vector<Bullet*>& bullets, float deltaTime);

void calcPartMovements(std::vector<Particle*>& particles, float deltaTime);

void checkCollisions(Ship* ship, std::vector<Asteroid*>& asteroids, std::vector<Bullet*>& bullets);

void checkAstDeletion(std::vector<Asteroid*>& asteroids);

void checkBulletDeletion(std::vector<Bullet*>& bullets);

void checkPartDeletion(std::vector<Particle*>& particles);

#endif