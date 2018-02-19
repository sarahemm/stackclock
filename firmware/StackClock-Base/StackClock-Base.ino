#include <EEPROM.h>
#include <SerialUI.h>
#include <Encoder.h>
#include <Wire.h>

#define FIRMWARE_VERSION 0

Encoder knob(PIN_ENC_B, PIN_ENC_A);

void setup() {
  cliInit();
  configInit();
  displaymgrInit();
  stackInit();
}

long oldPosition  = -999;

void loop() {
  char alphabet[27];
  char alpha_buffer[3];
  strcpy(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  
  long newPosition = knob.read() / 4;
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    strncpy(alpha_buffer, alphabet+newPosition, 3);
    stackSetAlpha(1, alpha_buffer);
  }
  
  cliServiceLoop();
}
