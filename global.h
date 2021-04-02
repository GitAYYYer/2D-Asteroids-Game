#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>
extern const int ORTHO_LEFT;
extern const int ORTHO_RIGHT;
extern const int ORTHO_DOWN;
extern const int ORTHO_UP;

extern const float ARENA_R;
extern const float ARENA_G;
extern const float ARENA_B;
extern const float ARENA_CENTER_X;
extern const float ARENA_CENTER_Y;
// Note: Width and Height is considered as the full amount from the origin, not half and half from origin
//      (so if equal to 400, it's 400 left from origin, and 400 right from origin)
extern const float ARENA_WIDTH;
extern const float ARENA_HEIGHT;
extern const float WARNING_DISTANCE;
extern const float ORBIT_RADIUS;

extern const float SHIP_MOVEMENT_SPEED;
extern const float SHIP_ROTATION_SPEED;

// Firing Rate -> 1 Bullet per X milliseconds
extern const float SHIP_FIRING_RATE;
extern const float BULLET_SPEED;
extern const int BULLET_SIZE;
extern const int BULLET_DMG;
extern const float BULLET_R;
extern const float BULLET_G;
extern const float BULLET_B;


extern const int PARTICLE_START_SIZE;
extern const int PARTICLE_DECAY_MS;
extern const int PARTICLE_AMT;
extern const int PARTICLE_MIN_ANGLE_OFFSET;
extern const int PARTICLE_MAX_ANGLE_OFFSET;

extern const int ASTEROID_SEGMENTS;
extern const int ASTEROID_MAX_VARIATIONS;
extern const int ASTEROID_MIN_RADIUS;
extern const int ASTEROID_MAX_RADIUS;
extern const float ASTEROID_MIN_SPEED;
extern const float ASTEROID_MAX_SPEED;
extern const float ASTEROID_MIN_ROT_SPEED;
extern const float ASTEROID_MAX_ROT_SPEED;
extern const float WAVE_COOLDOWN;

// 'X' units to the left from the center, 'X' units to the right from the center
extern const float PLAYER_WIDTH_HALF;
// Proportionate to the player width.
extern const float PLAYER_HEIGHT;
// Proportionate to the player width.
extern const float PLAYER_DOWN_LENGTH;

// Configurable outline RGB and face RGB
extern const float PLAYER_OUTLINE_R;
extern const float PLAYER_OUTLINE_G;
extern const float PLAYER_OUTLINE_B;
extern const float PLAYER_FILL_R;
extern const float PLAYER_FILL_G;
extern const float PLAYER_FILL_B;

extern bool NEW_GAME;
extern bool GAME_OVER;
extern bool RESTART_GAME;
extern int SCORE;
#endif