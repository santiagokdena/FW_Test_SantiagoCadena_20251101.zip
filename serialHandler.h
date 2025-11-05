#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H
#include "serialHandler.h"
#include "temperatureSensor.h"
#include "ledController.h"

class SerialHandler{
    public:
         void initialize();
         void update();
         void processCommand(String command);
    private:
         unsigned long lastUpdateTime;
         void printSystemStatus();
}
#endif
