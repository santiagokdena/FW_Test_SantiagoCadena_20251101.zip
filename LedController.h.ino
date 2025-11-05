#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H
#include "config.h"
class LedController{
  public:
    LedController();
    void initialize();
    void update();
    void setState(SystemState state);
    void TurnLeds(int pin, unsigned long interval);
    
  private:
    SystemState currentState;
    void updateNormalState();
    void updateAlertState();
    void updateDisabledState();
    unsigned long lastTime;
    bool blinkState=0;
}
#endif