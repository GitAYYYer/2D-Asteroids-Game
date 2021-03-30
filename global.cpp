#include "global.h"
// Probably better way than using three diff values?
extern const float ARENA_R = 0;
extern const float ARENA_G = 255;
extern const float ARENA_B = 0;
extern const float ARENA_WIDTH = 500;
extern const float ARENA_HEIGHT = 300;
extern const float WARNING_DISTANCE = 20;
extern const float ORBIT_RADIUS = 1200;

extern const float SHIP_MOVEMENT_SPEED = 0.2;
extern const float SHIP_ROTATION_SPEED = 0.3;

extern const float SHIP_FIRING_RATE = 500;
extern const float BULLET_SPEED = 0.3;
extern const int BULLET_SIZE = 6;
extern const int BULLET_DMG = 50;
extern const float BULLET_R = 0;
extern const float BULLET_G = 0;
extern const float BULLET_B = 255;

extern const int PARTICLE_START_SIZE = 5;
extern const int PARTICLE_DECAY_MS = 100;
extern const int PARTICLE_AMT = 3;
extern const int PARTICLE_MIN_ANGLE_OFFSET = -30;
extern const int PARTICLE_MAX_ANGLE_OFFSET = 30;

extern const int ASTEROID_SEGMENTS = 50;
extern const int ASTEROID_MAX_VARIATIONS = 10;
extern const int ASTEROID_MIN_RADIUS = 20;
extern const int ASTEROID_MAX_RADIUS = 50;
extern const float ASTEROID_MIN_SPEED = 0.05;
extern const float ASTEROID_MAX_SPEED = 0.2;
extern const float ASTEROID_MIN_ROT_SPEED = 0.1;
extern const float ASTEROID_MAX_ROT_SPEED = 0.3;
extern const float WAVE_COOLDOWN = 5.0;

// 'X' units to the left from the center, 'X' units to the right from the center
extern const float PLAYER_WIDTH_HALF = 25;
// Proportionate to the player width.
extern const float PLAYER_HEIGHT = PLAYER_WIDTH_HALF * 2;
// Proportionate to the player width.
extern const float PLAYER_DOWN_LENGTH = PLAYER_WIDTH_HALF * 0.4;

// Configurable outline RGB and face RGB
extern const float PLAYER_OUTLINE_R = 255;
extern const float PLAYER_OUTLINE_G = 0;
extern const float PLAYER_OUTLINE_B = 0;
extern const float PLAYER_FILL_R = 0;
extern const float PLAYER_FILL_G = 0;
extern const float PLAYER_FILL_B = 255;

bool GAME_OVER = false;
// keep track of how long the player lasted.
float TIME_ELAPSED = 0;
