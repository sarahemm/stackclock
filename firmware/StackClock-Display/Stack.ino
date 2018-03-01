// Stack - Handle talking to other components of the stack.

byte read_cmd;

void stackInit(void) {
  Wire.begin(1);  // TODO: this should be set via enumeration, not hard-coded
  Wire.onReceive(stackProcessCommand);
  Wire.onRequest(stackProcessReadRequest);
}

void stackProcessCommand(int numBytes) {
  byte cmd = Wire.read();
  switch (cmd) {
    case CMD_SETALPHA:
      char alpha_buf[3];
      alpha_buf[0] = Wire.read();
      alpha_buf[1] = Wire.read();
      alpha_buf[2] = Wire.read();
      alphaSetText(alpha_buf);
      break;
    case CMD_SETTIME:
      byte num_bytes, time_val;
      num_bytes = Wire.read();
      // this intentionally falls through
      switch (num_bytes) {
        case 3:
          time_val = Wire.read();
          numericSetHour(time_val);
        case 2:
          time_val = Wire.read();
          numericSetMinute(time_val);
        case 1:
          time_val = Wire.read();
          numericSetSecond(time_val);
          numericRefreshDisplays();
      }
      break;
    case CMD_IDENT:
      read_cmd = CMD_IDENT;
      break;
  }
}

void stackProcessReadRequest(void) {
  switch(read_cmd) {
    case CMD_NOOP:
      break;
    case CMD_IDENT:
      Wire.write(BOARD_TYPE);
      Wire.write(BOARD_HWREV);
      Wire.write(BOARD_FWREV);
      read_cmd = CMD_NOOP;
      break;
  }
}

