#include "textManager.h"

Text* timeAlive;
Text* score;
Text startGame("start", 0, 0);
Text gameOver("gameover", 0, 0);
TextManager::TextManager() {
    timeAlive = new Text(0, -900, 500);
    score = new Text(0, 900, 500);
    // Text score(0, -400, 500);
    // // init startGame and gameOver but do not display them
    // Text startGame("Press any key to start...", 0, 0);
    // Text gameOver("GAME OVER!", 0, 0);
}

void TextManager::drawText() {
    timeAlive->draw();
    score->draw();
    // startGame.draw();
    // this->score.drawText();
    // this->startGame.drawText();
    // this->gameOver.drawText();
}

void TextManager::updateText() {
    if (!GAME_OVER) {
        timeAlive->updateTimeAlive(glutGet(GLUT_ELAPSED_TIME));
        score->setBuffer(SCORE);
    }
}