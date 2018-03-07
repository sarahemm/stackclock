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
  timeInit();
  
  Serial.println("StackClock Base ready.");
}

byte last_second, last_minute, last_hour;

void loop() {
  if(!timeIsSet()) {
    timeSet(2017, 03, 06, 21, 43, 00);
    timeGet();
    stackSetTime(1, timeGetSecond(), timeGetMinute(), timeGetHour());
    stackSetAlpha(1, "QET");
  } else {
    timeGet();
    if(last_hour != timeGetHour()) {
      last_hour = timeGetHour();
      last_minute = timeGetMinute();
      last_second = timeGetSecond();
      stackSetTime(1, timeGetSecond(), timeGetMinute(), timeGetHour());
    } else if(last_minute != timeGetMinute()) {
      last_minute = timeGetMinute();
      last_second = timeGetSecond();
      stackSetTime(1, timeGetSecond(), timeGetMinute());
    } else if(last_second != timeGetSecond()) {
      last_second = timeGetSecond();
      stackSetTime(1, timeGetSecond());
    }
  }
  
  /*
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
  */
  
  //cliServiceLoop();
  delay(100);
}
