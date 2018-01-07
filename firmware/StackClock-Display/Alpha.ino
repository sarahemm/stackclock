void alphaInit(void) {
  pinMode(PIN_LED_nOE, OUTPUT);
  pinMode(PIN_LED_nSS, OUTPUT);
  pinMode(PIN_LED_SCK, OUTPUT);
  pinMode(PIN_LED_MOSI, OUTPUT);

  pinMode(PIN_DSP1_ANODE, OUTPUT);
  pinMode(PIN_DSP2_ANODE, OUTPUT);
//  pinMode(PIN_DSP3_ANODE, OUTPUT);
  digitalWrite(PIN_LED_nOE, HIGH);
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

