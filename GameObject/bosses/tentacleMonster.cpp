#include "tentacleMonster.h"

TentacleMonster::TentacleMonster() {
    int randomNumber = rand() % 200;
    float angle = 2.0f * M_PI * (float(randomNumber) / float(200));
    float radiusOfOrbit = ORBIT_RADIUS;

    this->x = ARENA_CENTER_X + radiusOfOrbit * cosf(angle);
    this->y = ARENA_CENTER_Y + radiusOfOrbit * sinf(angle);

    this->xRadius = 50;
    this->yRadius = 100;
    this->headHeight = this->yRadius * 1.5;
    this->headWidth = 30;
    this->speed = 0.2;
    this->theta = atan2(ARENA_CENTER_Y - this->y, ARENA_CENTER_X - this->x) * 180/M_PI;
    this->hp = 500;
    this->arms = 4;
    this->bodySegments = 200;
    this->currentYFluct = 0;
    this->armFluct = true;
    this->inArena = false;

    // Arms are evenly spaced between the body's number of segments
    int spreadAmt = this->bodySegments/(this->arms + 1);
    for (int i = 0; i < this->bodySegments; i++) {
        float angle = M_PI * (float(i) / float(this->bodySegments));
        float x = this->xRadius * cosf(angle);
        float y = this->yRadius * sinf(angle);

        if (i % spreadAmt == 0 && i != 0) {
            armCoords.push_back(std::make_tuple(x, -y));
        }
    }
}

void TentacleMonster::drawHead() {
    // Given you know x/y radius of body and x/y center, you know where head should be positioned
    // Give bit more to head width rather than just this->x
    glBegin(GL_LINE_LOOP);
    glColor3f(255, 0, 0);
    glVertex2f(this->x - this->xRadius - this->headWidth, this->y);
    glVertex2f(this->x + this->xRadius + this->headWidth, this->y);
    glVertex2f(this->x, this->y + this->headHeight);
    glEnd();
}

void TentacleMonster::drawBody() {
    glBegin(GL_LINE_LOOP);
    glColor3f(255, 0, 0);
    for (int i = 0; i <= this->bodySegments; i++) {
        float angle = M_PI * (float(i) / float(this->bodySegments));
        float x = this->xRadius * cosf(angle);
        float y = this->yRadius * -sinf(angle);
        glVertex2f(x + this->x, y + this->y);
    }
    glEnd();
}

// Eyes are two rotated half circles, same y level as the center
void TentacleMonster::drawEyes() {
    int segments = 200;
    float radius = 30;

    // Draw left eye
    glPushMatrix();
        float leftCenter = this->x - radius;
        glTranslatef(leftCenter, this->y, 0);
        glRotatef(135, 0, 0, 1);
        glTranslatef(-leftCenter, -this->y, 0);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float angle = M_PI * (float(i) / float(segments));
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);
            glVertex2f(x + leftCenter, y + this->y);
        }
        glEnd();
    glPopMatrix();

    // Draw right eye
    glPushMatrix();
        float rightCenter = this->x + radius;
        glTranslatef(rightCenter, this->y, 0);
        glRotatef(225, 0, 0, 1);
        glTranslatef(-rightCenter, -this->y, 0);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float angle = M_PI * (float(i) / float(segments));
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);
            glVertex2f(x + rightCenter, y + this->y);
        }
        glEnd();
    glPopMatrix();
}

float getBezierPoint(float t, float* ctrl) {
    return pow(1-t,3)*ctrl[0] + 3*t*pow(1-t,2)*ctrl[1] + 3*pow(t,2)*(1-t)*ctrl[2] + pow(t,3)*ctrl[3];
}

// First decide which direction the arm is going in (compare xStart to centerX)
// create control points by adding to the xStart, and fluctuate y control points too.
// draw points at every value returned by getBezierPoint
void TentacleMonster::drawArm(float xStart, float yStart, int armNumber) {
    int xLength = this->xRadius;
    if (xStart < this->x) {
        xLength = -xLength;
    }
    float yFluct = this->currentYFluct;
    float xCtrl[4]; xCtrl[0] = xStart; xCtrl[1] = xStart + xLength; xCtrl[2] = xStart + xLength*2; xCtrl[3] = xStart + xLength*3;
    // u should fluctuate y somehow, maybe get a random y val and add it to the yStart.
    float yCtrl[4]; yCtrl[0] = yStart; yCtrl[1] = yStart + yFluct; yCtrl[2] = yStart - yFluct*2; yCtrl[3] = yStart + this->endPointFluct;

    // I really cant be bothered how to figure this out properly.
    int rotationAmt = 10;
    if (armNumber == 0) {
        rotationAmt = -10;
    } else if (armNumber == 1) {
        rotationAmt = -40;
    } else if (armNumber == 2) {
        rotationAmt = 40;
    }

    glPushMatrix();
        glTranslatef(xStart, yStart, 0);
        glRotatef(rotationAmt, 0, 0, 1);
        glTranslatef(-xStart, -yStart, 0);

        glPointSize(3);
        glBegin(GL_POINTS);
        glColor3f(255, 255, 255);
        for (float t = 0; t <= 1; t += 0.01) {
            float x = getBezierPoint(t, xCtrl);
            float y = getBezierPoint(t, yCtrl);
            glVertex2f(x, y);
        }
        glEnd();
        glPointSize(1);
    glPopMatrix();

    if (armEndPtCoords.size() < 4) {
        armEndPtCoords.push_back(std::make_tuple(xCtrl[3], yCtrl[3]));
    } else {
        armEndPtCoords.at(armNumber) = std::make_tuple(xCtrl[3], yCtrl[3]);
    }
}

void TentacleMonster::drawArms() {
    glPushMatrix();
        for (int armCount = 0; armCount < this->arms; armCount++) {
            float xStart = this->x + get<0>(armCoords[armCount]);
            float yStart = this->y + get<1>(armCoords[armCount]);
            this->drawArm(xStart, yStart, armCount);
        }
    glPopMatrix();
}

void TentacleMonster::draw() {
    glLineWidth(3);
    drawHead();
    drawBody();
    drawEyes();
    drawArms();
    glLineWidth(1);
}

void TentacleMonster::changeArmFluct() {
    if (this->armFluct) {
        this->currentYFluct += 1;
    } else {
        this->currentYFluct -= 1;
    }
    if (this->currentYFluct >= 30 || this->currentYFluct <= -30) {
        this->armFluct = !this->armFluct;
    }

    int willFluct = rand() % 2;
    if (willFluct) {
        this->endPointFluct = (rand() % -5) + 5;
    }
}

float TentacleMonster::getX() {
    return x;
}

float TentacleMonster::getY() {
    return y;
}

int TentacleMonster::getXRadius() {
    return xRadius;
}

int TentacleMonster::getYRadius() {
    return yRadius;
}

int TentacleMonster::getHeadHeight() {
    return headHeight;
}

int TentacleMonster::getHeadWidth() {
    return headWidth;
}

float TentacleMonster::getSpeed() {
    return speed;
}

float TentacleMonster::getTheta() {
    return theta;
}

float TentacleMonster::getHp() {
    return hp;
}

bool TentacleMonster::getInArena() {
    return inArena;
}

float TentacleMonster::getLastShipX() {
    return lastShipX;
}

float TentacleMonster::getLastShipY() {
    return lastShipY;
}

void TentacleMonster::setX(float value) {
    x = value;
}

void TentacleMonster::setY(float value) {
    y= value;
}

void TentacleMonster::setXRadius(int value) {
    xRadius = value;
}

void TentacleMonster::setYRadius(int value) {
    yRadius = value;
}

void TentacleMonster::setHeadHeight(int value) {
    headHeight = value;
}

void TentacleMonster::setHeadWidth(int value) {
    headWidth = value;
}

void TentacleMonster::setSpeed(float value) {
    speed = value;
}

void TentacleMonster::setTheta(float value) {
    theta = value;
}

void TentacleMonster::setHp(float value) {
    hp = value;
}

void TentacleMonster::setInArena(bool value) {
    inArena = value;
}

void TentacleMonster::setLastShipX(float value) {
    lastShipX = value;
}

void TentacleMonster::setLastShipY(float value) {
    lastShipY = value;
}

vector< tuple<float, float> >& TentacleMonster::getArmCoords() {
    return armCoords;
}
vector <tuple<float, float> >& TentacleMonster::getArmEndPtCoords() {
    return armEndPtCoords;
}

float getRanFloat(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}