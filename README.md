## Interactive 3D Graphics and Animation - Asteroids
To run the project, make sure you're in the root directory (same level as main.cpp) and run the following: 
- clang++ *.cpp GameObject/*.cpp GameObject/bosses/*.cpp Math/*.cpp Manager/*.cpp -Wno-deprecated-declarations -framework GLUT -framework OpenGL -framework Carbon -std=c++14  -o main

Then run './main' to start the game.

## Configurables
To configure many aspects of the game (e.g. time between waves, orthogonal coordinates, etc), you can find them declared in global.h, and then have their values initialised in global.cpp. Configurables are:
- Ortho Coordinates: Lines 2-5 in global.cpp are used in main.cpp to determine the left, right, bottom and top values for the orthogonal space. The Arena has its width and height based off these coordinates, so as to be contained in them and only ever be smaller than the viewing space.
- Ship Movement: Lines 17-20 are for ship movement (acceleration/deceleration, movement speed and rotation speed).
- Bullet Properties: Lines 22-28 are for bullet properties (including the firing rate from the ship). 
- Particle Properties: Lines 30-40 are for particle properties, however they are split into particle properties for the ship, and particle properties for explosions in the game (in case you wanted to change them separately for different effect).
- Asteroid Properties: Lines 42-50 are for asteroid properties, including the cooldown in seconds between each wave.
- Black Hole Properties: Lines 52-63 are the black hole properties. BLACKHOLE_PULL_DISTANCE refers to the distance from the blackhole to the object where the object will start feeling the black hole pull. BLACKHOLE_MIN_PULL_POWER and BLACKHOLE_PULL_INTERVALS work together to determine strength of the blackhole to the object relative to the distance between them (basically, the more 'intervals' you are close to the blackhole, the stronger the pull).
- Player Properties: Lines 66-78 are the properties of the player, to determine player size and colours.
- Input: Lines 80-82 are the player input keys (the game will handle capital and lowercase of the keys).
The rest of the variables in global.cpp are meant to be related to the gameplay and change as the game state changes.

## Big Boss
Every 5th wave there spawns a big boss named Inkler :) Inkler spawns and moves into the arena, where he will have a 1/4 chance (this can be changed, but in the bossManager.cpp) to do something. If he does something, it will then be a 50/50 whether he shoots bullets at you or moves towards another place within the Arena.
Killing Inkler rewards you with 50 points, and extra attack speed.