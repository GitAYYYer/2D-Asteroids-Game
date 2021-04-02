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

using std::vector;

// Angle should be given in degrees
float sinD(float angle);
// Angle should be given in degrees
float cosD(float angle);

void calcShipMovement(Ship* ship, float deltaTime);
void calcAstMovements(vector<Asteroid*>& asteroids, float deltaTime);
void calcBulletMovements(vector<Bullet*>& bullets, float deltaTime);
void calcPartMovements(vector<Particle*>& particles, float deltaTime);

void checkCollisions(Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets);
void checkArenaShipCollision(Ship* ship);
void checkArenaBulletCollision(Ship* ship, vector<Bullet*>& bullets);
void checkAsteroidCollisions(Ship*, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets);

void checkAstDeletion(vector<Asteroid*>& asteroids);

void checkPartDeletion(vector<Particle*>& particles);

#endif