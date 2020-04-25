#include <Wire.h>
//#include <SeeedOLED.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
boolean newData = false;

float beatsPerMinute;
int beatAvg = 0, beatAvg_prev = 0;
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
//  initDisplay();
  initPulse();  
  delay(1000);
  Serial.println("Setup Done");
}

void loop() {
  getPulseData();
  checkNewData();
  if (newData) {
    Serial.println(beatAvg);
    Serial1.print(beatAvg);
//    SeeedOled.clearDisplay();
//    SeeedOled.setTextXY(0, 0);
//    SeeedOled.putString("Pulse: ");
//    SeeedOled.setTextXY(0, 7);
//    SeeedOled.putNumber(beatAvg);
  }
}
