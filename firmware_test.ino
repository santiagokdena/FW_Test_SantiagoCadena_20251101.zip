#include "DHT.h"

// Pin and constant definitions
#define DHTPIN 11
#define LED_B 7
#define Boton 2  // Pin for interrupt button
#define Uunits 100 // Units used for PI control
#define pwmMax 4095 // Maximum digital value reached by the controller
#define DHTTYPE DHT11 // Temperature sensor type
#define FAN_PWM_GPIO 9  // Define PWM output pin

DHT dht(DHTPIN, DHTTYPE);

// Global variables
long previousMillis = 0;
float Ref = 30.0; // Temperature reference value
float directCmd = 25.0;
float Cmd = 0.0; // Control output signal
float CmdPI = 0.0;       // PI control output signal
float E = 0.0, Ep = 0.0, Up = 0.0;  // Variables for error and control
long Ts = 1000; // Sampling time
unsigned int pwmDuty = 0; // Duty cycle
float tempF; // Current measured temperature
bool newData = false;    // For serial communication

// ADDED: System control variables
volatile bool systemEnabled = true; // System state (active/inactive)
volatile bool buttonFlag = false;   // Button pressed flag
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // Debounce time

// Variables for serial communication
const byte numChars = 32;
char receivedChars[numChars];

// Function prototypes
void ident(void);
void controlPI(void);
void analogWriteADJ(uint8_t pin, uint16_t val);
void recvWithStartEndMarkers();
void parseData();
void blink();
void stopAllActuators(); // ADDED: Function to stop actuators
void handleButtonPress(); // ADDED: Function to handle button press

// Button interruption - MODIFIED
void blink() {
  // Only set flag - processing in main loop
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonFlag = true;
  }
}

// ADDED: Function to stop all actuators
void stopAllActuators() {
  analogWriteADJ(LED_B, 0);          // Turn off LED
  analogWriteADJ(FAN_PWM_GPIO, 0);   // Turn off fan
  // Add other actuators here if you have them
  
  Serial.println("=== SYSTEM STOPPED ===");
  Serial.println("Press again to reactivate");
}

// ADDED: Function to handle button press
void handleButtonPress() {
  systemEnabled = !systemEnabled; // Toggle state
  lastDebounceTime = millis();
  
  if (!systemEnabled) {
    stopAllActuators();
  } else {
    Serial.println("=== SYSTEM REACTIVATED ===");
    // Reset control variables if necessary
    previousMillis = millis();
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(DHTPIN, INPUT); // CORRECTED: Should be INPUT for sensor
  pinMode(LED_B, OUTPUT);
  pinMode(Boton, INPUT_PULLUP);
  pinMode(FAN_PWM_GPIO, OUTPUT); // Configure PWM output pin
  
  digitalWrite(LED_B, LOW);
  
  // Configure interruption
  attachInterrupt(digitalPinToInterrupt(Boton), blink, FALLING);
  
  Serial.println("System started - Press button to stop/reactivate");
}

void loop() {
  // Handle button event
  if (buttonFlag) {
    buttonFlag = false;
    handleButtonPress();
  }
  
  // Only execute control if system is enabled
  if (systemEnabled) {
    ident();
    controlPI();
  }
  
  // Serial communication (always active)
  recvWithStartEndMarkers();
  if (newData == true) {
    parseData();
    newData = false;
  }
}

void ident() {
  if (!systemEnabled) return; // Do nothing if system disabled
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= Ts) {
    previousMillis = currentMillis;
    float Cmd = directCmd; // This is a local variable, not the global one
    float CmdLim = min(max(Cmd, 0), Uunits);
    float t = dht.readTemperature();
    
    pwmDuty = int((CmdLim / Uunits) * pwmMax);
    analogWriteADJ(LED_B, pwmDuty);
    
    Serial.print("Cmd:");
    Serial.print(CmdLim);
    Serial.print(" Temperature ");
    Serial.println(t);
  }
}

void controlPI(void) {
  if (!systemEnabled) return; // If the button is pressed, the whole system stops 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= Ts) {
    previousMillis = currentMillis;
    
    tempF = dht.readTemperature();
    float CmdLim = min(max(CmdPI, -50), 50);
    float Cmd = CmdLim + directCmd;
    pwmDuty = int((Cmd / 100) * pwmMax);
    
    analogWriteADJ(FAN_PWM_GPIO, pwmDuty);

    if (currentMillis >= 300000) { // Sampling is done every 3 seconds
      E = Ref - tempF;
      Ep = E;
      Up = CmdPI;
    }

    Serial.print("Error:");
    Serial.print(E);
    Serial.print(",U:");
    Serial.print(Cmd);
    Serial.print(",Ref:");
    Serial.print(Ref);
    Serial.print(",tempF:");
    Serial.println(tempF);
  }
}

// Definition of analogWriteADJ
void analogWriteADJ(uint8_t pin, uint16_t val) {
  // If you are on a standard Arduino, you can map the value to 0-255 and use analogWrite
  // But if your pwmMax is 4095, maybe you are on a 12-bit board?
  // Adjust according to your hardware.
  // For example, for Arduino Uno (8 bits), you would do:
  uint8_t duty8 = map(val, 0, pwmMax, 0, 255);
  analogWrite(pin, duty8);
}

// Functions for serial communication
void recvWithStartEndMarkers() {
  // Implementation of serial data reception
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedChars[ndx] = '\0';
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    } else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {
  // Implementation of data analysis
  // Example: split the data into parts
  char * strtokIndx;
  
  strtokIndx = strtok(receivedChars, ",");
  // Process the received data here
  
  // Example: if you want to control the system via serial too
  if (strcmp(receivedChars, "STOP") == 0) {
    systemEnabled = false;
    stopAllActuators();
  } else if (strcmp(receivedChars, "START") == 0) {
    systemEnabled = true;
    Serial.println("System reactivated by serial command");
  }
}