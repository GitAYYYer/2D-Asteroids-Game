#include "textManager.h"

Text* timeAlive;
Text* score;
Text* startGame;
Text* gameOver;
TextManager::TextManager() {
    timeAlive = new Text(0, 0, 0);
    score = new Text(0, 0, 0);
    startGame = new Text("Press any key to start...", 0, 0);
    gameOver = new Text("GAME OVER!", 0, 0);

    gameOver->setPos(-gameOver->calcWidth(gameOver->getBuffer())/2, -4);
    startGame->setPos(-startGame->calcWidth(startGame->getBuffer())/2, -4);
}

void TextManager::drawText() {
    timeAlive->draw();
    score->draw();

    if (GAME_OVER) {
        gameOver->draw();
    }
}

void TextManager::updateText() {
    if (!GAME_OVER) {
        timeAlive->updateTimeAlive(glutGet(GLUT_ELAPSED_TIME));
        score->updateScore(SCORE);
    }
}

void TextManager::resetText() {
    timeAlive->updateTimeAlive(0);
    score->setBuffer(0);
}