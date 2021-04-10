#include "global.h"
extern const int ORTHO_LEFT = -1000;
extern const int ORTHO_RIGHT = 1000;
extern const int ORTHO_DOWN = -600;
extern const int ORTHO_UP = 600;

extern const float ARENA_R = 0;
extern const float ARENA_G = 255;
extern const float ARENA_B = 0;
extern const float ARENA_CENTER_X = (ORTHO_RIGHT + ORTHO_LEFT) / 2;
extern const float ARENA_CENTER_Y = (ORTHO_UP + ORTHO_DOWN) / 2;
extern const float ARENA_WIDTH = sqrt(pow(ORTHO_RIGHT - ORTHO_LEFT, 2)) * 0.4;
extern const float ARENA_HEIGHT = sqrt(pow(ORTHO_UP - ORTHO_DOWN, 2)) * 0.4;
extern const float WARNING_DISTANCE = 100;
extern const float ORBIT_RADIUS = ARENA_WIDTH * 2;

extern const float SHIP_ACCELERATE_RATE = 0.009;
extern const float SHIP_DECELERATE_RATE = 0.02;
extern const float SHIP_MAX_MOVEMENT_SPEED = 0.3;
extern const float SHIP_ROTATION_SPEED = 0.3;

extern const float SHIP_FIRING_RATE = 400;
extern const float BULLET_SPEED = 0.5;
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

extern const int EXPLO_PARTICLE_START_SIZE = 5;
extern const int EXPLO_PARTICLE_AMT = 50;
extern const int EXPLO_PARTICLE_DECAY_MS = 100;
extern const float EXPLO_PARTICLE_MIN_SPEED = 0.2;
extern const float EXPLO_PARTICLE_MAX_SPEED = 0.6;

extern const int ASTEROID_SEGMENTS = 50;
extern const int ASTEROID_MAX_VARIATIONS = 10;
extern const int ASTEROID_MIN_RADIUS = 20;
extern const int ASTEROID_MAX_RADIUS = 50;
extern const float ASTEROID_MIN_SPEED = 0.05;
extern const float ASTEROID_MAX_SPEED = 0.1;
extern const float ASTEROID_MIN_ROT_SPEED = 0.1;
extern const float ASTEROID_MAX_ROT_SPEED = 0.5;
extern const float WAVE_COOLDOWN = 10.0;

extern const int BLACKHOLE_PULSE_AMT = 5;
extern const int BLACKHOLE_PULSE_RATE_MS = 500;
extern const int BLACKHOLE_MIN_RADIUS = 20;
extern const int BLACKHOLE_MAX_RADIUS = 40;
extern const float BLACKHOLE_PULL_DISTANCE = 300;
extern const int BLACKHOLE_BULLET_PULL_MULTIPLIER = 6;
extern const float BLACKHOLE_MIN_PULL_POWER = 0.8;
// For every X intervals closer you are to the black hole, increase the pull power
extern const float BLACKHOLE_PULL_INTERVALS = 100;
extern const float BLACKHOLE_R = 0;
extern const float BLACKHOLE_G = 100;
extern const float BLACKHOLE_B = 255;

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

bool NEW_GAME = true;
bool GAME_OVER = false;
bool RESTART_GAME = false;
int SCORE = 0;
bool GOD_MODE = false;