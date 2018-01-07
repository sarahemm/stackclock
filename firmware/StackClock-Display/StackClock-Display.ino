#include <Wire.h>
#include "AlphaFont.h"
#include "StackProtocol.h"

byte alpha_buffer[3];

void setup() {
  Serial.begin(38400);
  Serial.println("StackClock Display ready.");
  
  alphaInit();
  
  Wire.begin(1);  // TODO: this should be set via enumeration, not hard-coded
  Wire.onReceive(onWireReceive);
  alpha_buffer[0] = '-';
  alpha_buffer[1] = '-';
  alpha_buffer[2] = '-';
}

void loop() {
  /*
  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[0]] >> 8) & 0xFF);
  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[0]] & 0xFF);
  alphaDisplayOn(PIN_DSP2_ANODE);
  delay(50);
  alphaDisplayOff(PIN_DSP2_ANODE);
  */

  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[1]] >> 8) & 0xFF);
  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[1]] & 0xFF);
  alphaDisplayOn(PIN_DSP1_ANODE);
  delay(10);
  alphaDisplayOff(PIN_DSP1_ANODE);

  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[2]] >> 8) & 0xFF);
  shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[2]] & 0xFF);
  alphaDisplayOn(PIN_DSP2_ANODE);
  delay(10);
  alphaDisplayOff(PIN_DSP2_ANODE);
}


void onWireReceive(int numBytes) {
  byte cmd = Wire.read();
  switch(cmd) {
    case CMD_SETALPHA:
      alpha_buffer[0] = Wire.read();
      alpha_buffer[1] = Wire.read();
      alpha_buffer[2] = Wire.read();
      break;
  }
}


