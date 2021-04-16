#ifndef BOSS_MATH_H
#define BOSS_MATH_H
#include "../GameObject/bosses/tentacleMonster.h"
#include "../GameObject/ship.h"
#include "../GameObject/asteroid.h"
#include "../GameObject/bullet.h"
#include "../GameObject/blackhole.h"
#include "../Manager/waveManager.h"
#include "../Manager/bulletManager.h"
#include "../Manager/particleManager.h"
#include "../Manager/bossManager.h"

using std::vector;

void calcTentacleMonsterMovement(TentacleMonster* tm, float deltaTime);
void calcBossBulletMovement(vector<Bullet*>& bullets, float deltaTime);

void calcBossCollision(BossManager* bm, Ship* ship, vector<Asteroid*>& asteroids, vector<Bullet*>& bullets, ParticleManager* particleManager);
void calcShipCollision(TentacleMonster* tm, Ship* ship);
void calcAstCollision(TentacleMonster* tm, vector<Asteroid*>& asteroids, ParticleManager* particleManager);
void calcBullCollision(TentacleMonster* tm, vector<Bullet*>& bullets);
void calcBossBulletsCollision(Ship* ship, BlackHole* blackHole, vector<Bullet*>& bullets);
void calcBlackHoleBulletPull(BlackHole* blackHole, vector<Bullet*>& bullets);

#endif