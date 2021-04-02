#include "textManager.h"

Text* timeAlive;
Text* score;
Text* newGame;
Text* gameOver;
TextManager::TextManager() {
    previousResetTime = 0;
    timeAlive = new Text(0, 0, 0, GLUT_BITMAP_8_BY_13);
    score = new Text(0, 0, 0, GLUT_BITMAP_8_BY_13);
    newGame = new Text("Press any key to start...", 0, 0, GLUT_BITMAP_8_BY_13);
    gameOver = new Text("GAME OVER! Press any key to play again...", 0, 0, GLUT_BITMAP_8_BY_13);

    timeAlive->updateTimeAlive(0);
    score->updateScore(0);
    newGame->setPos(ARENA_CENTER_X, ARENA_CENTER_Y);
    gameOver->setPos(ARENA_CENTER_X, ARENA_CENTER_Y);
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
    if (NEW_GAME) {
        previousResetTime = glutGet(GLUT_ELAPSED_TIME);
    }
    if (!GAME_OVER && !NEW_GAME) {
        timeAlive->updateTimeAlive(glutGet(GLUT_ELAPSED_TIME) - previousResetTime);
        score->updateScore(SCORE);
    }
}

void TextManager::reset() {
    previousResetTime = glutGet(GLUT_ELAPSED_TIME);
}