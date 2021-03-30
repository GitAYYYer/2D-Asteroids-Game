#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H
#include "../GameObject/text.h"
#include "../global.h"
#include "string"

class TextManager {
    private:
        // Text* timeAlive(int number, float x, float y);
        // Text score(1, 1, 1);
        // Text startGame("Start", 1, 1);
        // Text gameOver("GameOver", 1, 1);
    public:
        TextManager();
        void drawText();
        void updateText();
};

#endif