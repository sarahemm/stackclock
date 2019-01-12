#include <TimerOne.h>
#include <Wire.h>
#include <AS1115.h>
#include "Stack.h"

#define BOARD_TYPE  0x01
#define BOARD_HWREV 0x01  // this should be settable in hardware somehow
#define BOARD_FWREV 0x00

void setup() {
  Serial.begin(38400);
  Serial.println("StackClock Display ready.");

  alphaInit();
  numericInit();
  stackInit();
}

void loop() {
  // process any commands waiting in the queue
  stackProcessQueue();
}

