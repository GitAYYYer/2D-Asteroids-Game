#ifndef BOSS_MATH_H
#define BOSS_MATH_H
#include "../GameObject/bosses/tentacleMonster.h"
#include "../GameObject/ship.h"
#include "../GameObject/asteroid.h"
#include "../GameObject/bullet.h"
#include "../Manager/waveManager.h"
#include "../Manager/bulletManager.h"
#include "../Manager/particleManager.h"

using std::vector;

void calcTentacleMonsterMovement(TentacleMonster* tm, float deltaTime);

void calcBossCollision(TentacleMonster* tm, Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets);
void calcShipCollision(TentacleMonster* tm, Ship* ship);
void calcAstCollision(TentacleMonster* tm, vector<Asteroid*>& asteroids);

#endif