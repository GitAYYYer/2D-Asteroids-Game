#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H
#include "../GameObject/text.h"
#include "../global.h"
#include "string"

class TextManager {
    private:
        int previousResetTime;
    public:
        TextManager();
        void drawText();
        void updateText();
        void reset();
};

#endif