// Numeric - Handle setting the numeric displays.

/*
(AS1115 channel numbers, for library's idea of numbers subtract 1)

   11111
  7     2
  7     2
  7     2
   88888
  5     3
  5     3
  5     3
   44444  6

*/
#include "NumericFont.h"

// display aren't hooked up to the pins you'd expect, this maps logical display to physical display
byte display_map[] = {2, 6, 5, 4, 1, 3};

byte numeric_buffer[8];

AS1115 num_disp = AS1115(0x03, 1);

void numericInit() {
  // set up the AS1115 that drives the numeric displays
  num_disp.begin();
  
  // we can't use the built in AS1115 fonts because we use the
  // chip "backwards" (segs connected to digit pins and vice-versa)
  num_disp.setDecode(DECODE_ALL_RAW);

  memset(&numeric_buffer, ' ', 6);
  numericRefreshDisplays();
}

void numericSetDigit(byte digit, byte value) {
  numeric_buffer[digit] = value;
}

void numericSetHour(byte hours) {
  char time_str[3];

  sprintf(time_str, "%02d", hours);
  numeric_buffer[0] = time_str[0] - '0';
  numeric_buffer[1] = time_str[1] - '0';
}

void numericSetMinute(byte mins) {
  char time_str[3];

  sprintf(time_str, "%02d", mins);
  numeric_buffer[2] = time_str[0] - '0';
  numeric_buffer[3] = time_str[1] - '0';
}

void numericSetSecond(byte secs) {
  numeric_buffer[4] = secs / 10;
  numeric_buffer[5] = secs % 10;
}

// pivot the data in the buffer to fit the weird way we address displays and write it out
// what the AS1115 calls a 'display' is actually a segment across all displays
// what the AS1115 calls a 'segment' is actually a display
void numericRefreshDisplays(void) {
  byte display_buffer[10];
  byte seg_nbr, display_nbr;

  memset(&display_buffer, 0, 9);
  
  // pivot the array so displays become segments and vice-versa
  // also map the display numbers since display 0 isn't the leftmost, etc.
  for(display_nbr=0; display_nbr<=5; display_nbr++) {
    for(seg_nbr=0; seg_nbr<=7; seg_nbr++) {
      if(numeric_font[numeric_buffer[display_nbr]] & (1 << seg_nbr)) {
        display_buffer[seg_nbr] |= 1 << display_map[display_nbr];
      }
    }
  }

  // write the pivoted array out to the segment registers
  for(seg_nbr=0; seg_nbr<=7; seg_nbr++) {
    num_disp.digitWrite(seg_nbr, display_buffer[seg_nbr]);
  }
}

