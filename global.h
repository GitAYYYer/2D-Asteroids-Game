#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>
// Arena Related
extern const float ARENA_R;
extern const float ARENA_G;
extern const float ARENA_B;
// Note: Width and Height is considered as the full amount from the origin, not half and half from origin
//      (so if equal to 400, it's 400 left from origin, and 400 right from origin)
extern const float ARENA_WIDTH;
extern const float ARENA_HEIGHT;
extern const float WARNING_DISTANCE;
extern const float ORBIT_RADIUS;

extern const float SHIP_MOVEMENT_SPEED;
extern const float SHIP_ROTATION_SPEED;

extern const int PARTICLE_START_SIZE;
extern const int PARTICLE_DECAY_MS;
extern const int PARTICLE_AMT;
extern const int PARTICLE_MIN_ANGLE_OFFSET;
extern const int PARTICLE_MAX_ANGLE_OFFSET;

extern const int ASTEROID_MIN_RADIUS;
extern const int ASTEROID_MAX_RADIUS;
extern const float ASTEROID_MIN_SPEED;
extern const float ASTEROID_MAX_SPEED;
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

extern bool GAME_OVER;
extern float TIME_ELAPSED;

#endif