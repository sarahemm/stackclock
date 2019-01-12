// Stack - Handle talking to other components of the stack.

byte read_cmd;

void stackInit(void) {
  Wire.begin(1);  // TODO: this should be set via enumeration, not hard-coded
  Wire.onReceive(stackReceiveCommand);
  Wire.onRequest(stackProcessReadRequest);
}

byte wire_buf[32];
byte wire_buf_len = 0;

void stackReceiveCommand(int num_bytes) {
  if(num_bytes > 8) {
    Serial.println("Very long message received, ignoring!");
    // consume the whole message so we can at least try to keep functioning
    // if we leave any bytes in the buffer when returning, we'll never get called again
    while(Wire.available()) {
      Wire.read();
    }
    return;
  }

  byte i;
  for(i=wire_buf_len; i<num_bytes+wire_buf_len; i++) {
    wire_buf[i] = Wire.read();
  }
  
  wire_buf_len += num_bytes; 
}

void stackProcessQueue(void) {
  while(wire_buf_len > 0) {
    byte cmd_len = 0;
    byte cmd = wire_buf[0];
    cmd_len++;
    
    //Serial.print("CMD 0x");
    //Serial.println(cmd, HEX);
    
    switch (cmd) {
      case CMD_SETALPHA:
        alphaSetText((char *)&wire_buf[1]);
        cmd_len += 3;
        break;
      case CMD_SETTIME:
        byte num_bytes, time_val;
        num_bytes = wire_buf[1];
        cmd_len++;
        // this intentionally falls through
        switch (num_bytes) {
          case 3:
            time_val = wire_buf[4];
            numericSetHour(time_val);
            cmd_len++;
          case 2:
            time_val = wire_buf[3];
            numericSetMinute(time_val);
            cmd_len++;
          case 1:
            time_val = wire_buf[2];
            numericSetSecond(time_val);
            numericRefreshDisplays();
            cmd_len++;
        }
        break;
      case CMD_IDENT:
        read_cmd = CMD_IDENT;
        break;
    }

    /*byte i;
    Serial.println("Before memmove...");
    for(i=0; i<16; i++) {
      Serial.print(i, DEC);
      Serial.print(": 0x");
      Serial.println(wire_buf[i]);
    }
    */
    // shift anything left in the buffer to the beginning
    memmove(wire_buf, wire_buf+cmd_len, wire_buf_len - cmd_len);
    /*
    Serial.println("After memmove...");
    for(i=0; i<16; i++) {
      Serial.print(i, DEC);
      Serial.print(": 0x");
      Serial.println(wire_buf[i]);
    }
    */
    
    wire_buf_len -= cmd_len;
    //Serial.print("Length left after: ");
    //Serial.println(wire_buf_len);
  }
}

void stackProcessReadRequest(void) {
  Serial.print("ReadReq");
  
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
  Serial.println(" done.");
}

