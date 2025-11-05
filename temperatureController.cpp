#include "temperatureController.h"

void TemperatureSensor::initialize(){
pinMode(TERMOSTAT,INPUT);
Serial.println("Temperatura iniciada");
}
void TemperatureSensor::update(){
    unsigned long currentTime=millis();
    if(currentTime-lastReadTime >=1000){
        currentTemperature=readSensor();
        lastReadTime=currentTime;
        Serial.print("Temperatura: ");
        Serial.print(currentTemperature);
        Serial.println(" °C");
    }
}
float TemperatureSensor::getTemperature(){
    return currentTemperature;
}
bool TemperatureSensor::isAlert(){
    return currentTemperature > TEMPERATURE_ALERT;
}
float TemperatureSensor::readSensor(){
    int raw = analogRead(PIN_SENSOR_TEMP);
    float voltage = (rawValue*5.0)/1024;
    return (voltage-5.0)*100;
}