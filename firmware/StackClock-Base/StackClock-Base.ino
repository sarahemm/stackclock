#include <EEPROM.h>
#include <SerialUI.h>
#include <Encoder.h>
#include <Wire.h>

#define BOARD_TYPE  0x00
#define BOARD_HWREV 0x01  // this should be settable in hardware somehow
#define BOARD_FWREV 0x00

Encoder knob(PIN_ENC_B, PIN_ENC_A);

void setup() {
  Serial.begin(115200);
  //cliInit();
  configInit();
  displaymgrInit();
  stackInit();

  Serial.println("StackClock Base ready.");
}

long oldPosition  = -999;

void loop() {
  char alphabet[27];
  char alpha_buffer[3];
  strcpy(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  
  long newPosition = knob.read() / 4;
  if (newPosition != oldPosition) {
    Serial.println("Knob twiddled!");
    stackSetTime(1, oldPosition, 0, newPosition);
    oldPosition = newPosition;
    Serial.println(newPosition);
    strncpy(alpha_buffer, alphabet+newPosition, 3);
    stackSetAlpha(1, alpha_buffer);
  }

  //cliServiceLoop();
}
