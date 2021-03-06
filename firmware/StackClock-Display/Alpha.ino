// Alpha - Handle setting the alphanumeric displays.

#include "AlphaFont.h"

char alpha_buffer[3];

void alphaInit(void) {
  pinMode(PIN_LED_nOE, OUTPUT);
  pinMode(PIN_LED_nSS, OUTPUT);
  pinMode(PIN_LED_SCK, OUTPUT);
  pinMode(PIN_LED_MOSI, OUTPUT);

  pinMode(PIN_DSP1_ANODE, OUTPUT);
  pinMode(PIN_DSP2_ANODE, OUTPUT);
//  pinMode(PIN_DSP3_ANODE, OUTPUT);
  digitalWrite(PIN_LED_nOE, HIGH);

  memset(&alpha_buffer, ' ', 3);

  // set up a timer callback for every 10ms so we can manually mux the display
  Timer1.initialize(7500);
  Timer1.attachInterrupt(alphaRefreshDisplays);
}

void alphaDisplayOff(byte displayPin) {
  digitalWrite(PIN_LED_nOE, HIGH);
  digitalWrite(displayPin, LOW);
}

void alphaDisplayOn(byte displayPin) {
  digitalWrite(PIN_LED_nSS, LOW);
  digitalWrite(PIN_LED_nSS, HIGH);
  digitalWrite(PIN_LED_nOE, LOW);
  digitalWrite(displayPin, HIGH);
}

void alphaSetText(char *text) {
  strncpy(alpha_buffer, text, 3);
  Serial.println(text[0], DEC);
  Serial.println(text[1], DEC);
  Serial.println(text[2], DEC);
}

void alphaRefreshDisplays(void) {
  static byte char_nbr = 0;
  // each time we're called we switch to displaying the next character
  switch(char_nbr) {
    case 0:
      alphaDisplayOff(PIN_DSP2_ANODE);
      //shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[0]] >> 8) & 0xFF);
      //shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[0]] & 0xFF);
      //alphaDisplayOn(PIN_DSP2_ANODE);
      //delay(50);
      //alphaDisplayOff(PIN_DSP2_ANODE);
      char_nbr++;
      break;
    case 1:
      shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[1]] >> 8) & 0xFF);
      shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[1]] & 0xFF);
      alphaDisplayOn(PIN_DSP1_ANODE);
      char_nbr++;
      break;
    case 2:
      alphaDisplayOff(PIN_DSP1_ANODE);
      shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, (alpha_font[alpha_buffer[2]] >> 8) & 0xFF);
      shiftOut(PIN_LED_MOSI, PIN_LED_SCK, MSBFIRST, alpha_font[alpha_buffer[2]] & 0xFF);
      alphaDisplayOn(PIN_DSP2_ANODE);
      char_nbr = 0;
      break;
  }
}

