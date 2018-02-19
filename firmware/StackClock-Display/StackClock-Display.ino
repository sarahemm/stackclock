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
  
  Wire.begin(1);  // TODO: this should be set via enumeration, not hard-coded
  Wire.onReceive(stackProcessCommand);
  Wire.onRequest(stackProcessReadRequest);
}

void loop() {
  // this must be called frequently as it muxes the displays by hand
  alphaRefreshDisplays();
}

