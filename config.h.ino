#ifndef CONFIG_H
#define CONFIG_H

#define PHOTORESISTOR A4
#define CO2_DETECTOR A3
#define BUZZER 2
#define FAN A2
#define TERMOSTAT A1
#define BUTTON A0

int LED_PINS[4]={12,11,10,9};

// System parameters

const unsigned long main_delay=100;
const float temperature_alert = 26.0f;

enum SystemState{
  automatic,
  alert,
  stopped
}
#endif
