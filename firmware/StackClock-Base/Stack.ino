// Stack - Handle talking to other components of the stack.

#include "Stack.h"

void stackInit(void) {
  Wire.begin();
}

void stackSetAlpha(byte stackAddress, char *text) {
  Serial.println("Alpha Set Start");
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETALPHA);
  Wire.write((char)*text);
  Wire.write((char)*text+1);
  Wire.write((char)*text+2);
  Serial.println("Alpha Set End");
  Wire.endTransmission();
  Serial.println("Alpha Set Done");
}

void stackSetTime(byte stackAddress, byte hour, byte minute, byte second) {
  Serial.println("Num Set Start");
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETTIME);
  Wire.write(3); // we're setting all 3 time components
  Wire.write(second);
  Wire.write(minute);
  Wire.write(hour);
  Serial.println("Num Set End");
  Wire.endTransmission();
  Serial.println("Num Set Done");
}

