#include "textManager.h"

Text* timeAlive;
Text* score;
Text* newGame;
Text* gameOver;
TextManager::TextManager() {
    previousResetTime = 0;
    timeAlive = new Text(0, 0, 0);
    score = new Text(0, 0, 0);
    newGame = new Text("Press any key to start...", 0, 0);
    gameOver = new Text("GAME OVER! Press any key to play again...", 0, 0);

    timeAlive->updateTimeAlive(0);
    score->updateScore(0);
    gameOver->setPos(-gameOver->calcWidth(gameOver->getBuffer())/2, -4);
    newGame->setPos(-newGame->calcWidth(newGame->getBuffer())/2, -4);
}

void TextManager::drawText() {
    timeAlive->draw();
    score->draw();
    
    if (NEW_GAME) {
        newGame->draw();
    }
    if (GAME_OVER) {
        gameOver->draw();
    }
}

void TextManager::updateText() {
    if (!GAME_OVER && !NEW_GAME) {
        timeAlive->updateTimeAlive(glutGet(GLUT_ELAPSED_TIME) - previousResetTime);
        score->updateScore(SCORE);
    }
}

void TextManager::reset() {
    previousResetTime = glutGet(GLUT_ELAPSED_TIME);
}