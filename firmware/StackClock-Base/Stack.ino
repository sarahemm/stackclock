// Stack - Handle talking to other components of the stack.

void stackInit(void) {
  Wire.begin();
}

void stackSetAlpha(byte stackAddress, char text[3]) {
  Wire.beginTransmission(stackAddress);
  Wire.write(stackAddress);
  Wire.write(text[0]);
  Wire.write(text[1]);
  Wire.write(text[2]);
  Wire.endTransmission(stackAddress);
}

