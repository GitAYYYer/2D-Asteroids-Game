#include "arena.h"

Arena::Arena() {
    xCoord = ARENA_WIDTH;
    yCoord = ARENA_HEIGHT;
    orbitRadius =  ORBIT_RADIUS;
}

void Arena::draw(Ship* ship) {
    // Draw Arena as LINE_LOOP
    glBegin(GL_LINE_LOOP);
    checkWarningDistance(ship);
    glVertex2f(-1 * xCoord, yCoord);
    glVertex2f(xCoord, yCoord);
    glVertex2f(xCoord, -1 * yCoord);
    glVertex2f(-1 * xCoord, -1 * yCoord);
    glEnd();
}

// Method is for DEBUGGING the orbit.
// void drawOrbit() {
//     int segments = 1000;
//     glBegin(GL_LINE_LOOP);
//         glColor3f(255, 255, 255);
//         for(int i = 0; i < segments; i++) {
//             float angle = 2.0f * M_PI * (float(i) / float(segments));
//             float radiusOfOrbit = ORBIT_RADIUS;
//             // x and y here represent a random coordinate on the orbit that goes around the arena.
//             float x = radiusOfOrbit * cosf(angle);
//             float y = radiusOfOrbit * sinf(angle);
//             glVertex2f(x, y);
//         }
//     glEnd();
// }

void Arena::checkWarningDistance(Ship* ship) {
    // Calculate where bounding circle of ship is in relation to arena wall
    // If within warning distance, change arena colour to red.
    // If distance <= 0, then game over (maybe have a global bool that you set true, and main will check that bool?)

    bool displayWarning = false;
    int segments = 500;
    for(int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * (float(i) / float(segments));
        float radius = PLAYER_HEIGHT - 12;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);

        // Check each wall individually, to check with respect to y or x for horizontal or vertical walls.
        // Order will be top, right, bottom, left
        if (ARENA_HEIGHT - (ship->getY() + radius) <= WARNING_DISTANCE) {
            displayWarning = true;
        } else if (ARENA_WIDTH - (ship->getX() + radius) <= WARNING_DISTANCE) {
            displayWarning = true;
        // +20 to make the distance to display warning smaller
        } else if (ARENA_HEIGHT + (ship->getY() - radius + 20) <= WARNING_DISTANCE) {
            displayWarning = true;
        } else if (ARENA_WIDTH + (ship->getX() - radius) <= WARNING_DISTANCE) {
            displayWarning = true;
        }
    }
    
    if (displayWarning) {
        glColor3f(255, 0, 0);
    } else {
        glColor3f(ARENA_R, ARENA_G, ARENA_B);
    }
}