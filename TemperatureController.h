#ifndef TEMPERATURECONTROLLER_H
#define TEMPERATURECONTROLLER_H

#include "config.h"

class TemperatureController{
    public:
        TemperatureSensor();
        void initialize();
        void update();
        float getTemperature();
        bool isAlert();
    private: 
        float currentTemperature;

}