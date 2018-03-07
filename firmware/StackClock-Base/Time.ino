// Time - Handle keeping track of the time.

#include "RTClib.h"

RTC_Millis rtc;
bool time_set = false;

void timeInit(void) {
  
}

bool timeIsSet(void) {
  return time_set;
}

void timeSet(int years, int months, int days, int hours, int mins, int secs) {
  rtc.begin(DateTime(years, months, days, hours, mins, secs));
  time_set = true;
}

DateTime time_buf;

void timeGet(void) {
  // capture the time into the buffer for later reading out
  time_buf = rtc.now();
}

byte timeGetHour(void) {
  return time_buf.hour();
}

byte timeGetMinute(void) {
  return time_buf.minute();
}
byte timeGetSecond(void) {
  return time_buf.second();
}

