// Stack - Handle talking to other components of the stack.

#include "Stack.h"

void stackInit(void) {
  Wire.begin();
}

void stackSetAlpha(byte stackAddress, char *text) {
  char buf[3];
  strncpy(buf, text, 3);
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETALPHA);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.write(buf[2]);
  Wire.endTransmission();
}

void stackSetTime(byte stackAddress, byte second, byte minute, byte hour) {
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETTIME);
  Wire.write(3); // we're setting all 3 time components
  Wire.write(second);
  Wire.write(minute);
  Wire.write(hour);
  Wire.endTransmission();
}

void stackSetTime(byte stackAddress, byte second, byte minute) {
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETTIME);
  Wire.write(2); // we're setting just the minutes and seconds
  Wire.write(second);
  Wire.write(minute);
  Wire.endTransmission();
}

void stackSetTime(byte stackAddress, byte second) {
  Wire.beginTransmission(stackAddress);
  Wire.write(CMD_SETTIME);
  Wire.write(1); // we're setting just the seconds
  Wire.write(second);
  Wire.endTransmission();
}

