#include <EEPROM.h>

#include <Boards.h>
#include <Firmata.h>

#include "FastLED.h"

#define NUM_LEDS 30

// Data pin that led data will be written out over
#define DATA_PIN 5
// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8
int addr = 0;
// Variable to store input string
String config_cmd;

CRGB leds[NUM_LEDS];
int R,G,B;
// For Brightness: B000-B100 (not implemented)
// Color Value: *xxxxxxxxx#

void setColorValuesFromEeprom(){
    R=EEPROM.read(0);
    G=EEPROM.read(1);
    B=EEPROM.read(2);
    for(int i=1;i<=NUM_LEDS; i++) {
      leds[i] = CRGB(R,G,B);
    }
    FastLED.show();
}

void readSerial() {
  config_cmd = Serial.readStringUntil('#');
  if (config_cmd.startsWith("*")) {
    config_cmd.remove(0,1);
    Serial.println(config_cmd);
    EEPROM.update(0,(int)config_cmd.substring(0,3).toInt());
    EEPROM.update(1, (int)config_cmd.substring(3,6).toInt());
    EEPROM.update(2, (int)config_cmd.substring(6).toInt());
  }
}

void setup() {
   	delay(2000);
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    EEPROM.write(0, 255); // Red
    EEPROM.write(1,0);    // Green
    EEPROM.write(2,0);    // Blue
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
}

void loop() {
   setColorValuesFromEeprom();
   if (Serial.available() > 0) {
      readSerial();
   }
   delay(1000);
}
