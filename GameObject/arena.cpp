#include "arena.h"

Arena::Arena() {
    xCenter = ARENA_CENTER_X;
    yCenter = ARENA_CENTER_Y;
    orbitRadius =  ORBIT_RADIUS;
}

void Arena::draw(Ship* ship) {
    glBegin(GL_LINE_LOOP);
    checkWarningDistance(ship);
    glVertex2f(xCenter - ARENA_WIDTH, yCenter + ARENA_HEIGHT);
    glVertex2f(xCenter + ARENA_WIDTH, yCenter + ARENA_HEIGHT);
    glVertex2f(xCenter + ARENA_WIDTH, yCenter - ARENA_HEIGHT);
    glVertex2f(xCenter - ARENA_WIDTH, yCenter - ARENA_HEIGHT);
    glEnd();
    drawOrbit();
}

// Method is for DEBUGGING the orbit.
void drawOrbit() {
    int segments = 1000;
    glBegin(GL_LINE_LOOP);
        glColor3f(255, 255, 255);
        for(int i = 0; i < segments; i++) {
            float angle = 2.0f * M_PI * (float(i) / float(segments));
            float radiusOfOrbit = ORBIT_RADIUS;
            // x and y here represent a random coordinate on the orbit that goes around the arena.
            float x = ARENA_CENTER_X + radiusOfOrbit * cosf(angle);
            float y = ARENA_CENTER_Y + radiusOfOrbit * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

void Arena::checkWarningDistance(Ship* ship) {
    bool displayWarning = false;
    // Note: For the top and bottom wall, you do not need to calculate x2 - x1, since the xCoord does not matter.
    // - Likewise the same for left and right wall with yCoord.
    float topWallDist = sqrt(pow(ARENA_CENTER_Y + ARENA_HEIGHT - ship->getY(), 2));
    float botWallDist = sqrt(pow(ARENA_CENTER_Y - ARENA_HEIGHT - ship->getY(), 2));
    float leftWallDist = sqrt(pow(ARENA_CENTER_X - ARENA_WIDTH - ship->getX(), 2));
    float rightWallDist = sqrt(pow(ARENA_CENTER_X + ARENA_WIDTH - ship->getX(), 2));

    if (topWallDist <= WARNING_DISTANCE || botWallDist <= WARNING_DISTANCE || leftWallDist <= WARNING_DISTANCE || rightWallDist <= WARNING_DISTANCE) {
        displayWarning = true;
    }
    
    if (displayWarning) {
        glColor3f(255, 0, 0);
    } else {
        glColor3f(ARENA_R, ARENA_G, ARENA_B);
    }
}