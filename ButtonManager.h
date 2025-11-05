#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "config.h"

class ButtonManager{
    public:
        ButtonManager();
        void intialize();
        void update();
        int getPressCount();
        void resetPressCount();
        bool isNewPressAvailable();
    private:
        int buttonState;
        int lastButtonState;
        unsigned long lastDebounceTime;
        unsigned long lastPressTime;
           
        int pressCount;
        bool newPressAvailable;

        void handleButtonPress();
        void handleMultiPress();
}
#endif