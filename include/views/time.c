
void updateMainClock(void) {
  DS1307GetTime(&current_time);
  if (last_minutes != current_time.minutes || last_hours != current_time.hours) {
    char buf[10];
    sprintf(buf,"%02u:%02u", current_time.hours, current_time.minutes);
    nlcd_Text(buf,CLOCK_OFFSET_Y,CLOCK_OFFSET_X,BLACK,WHITE);
    last_minutes = current_time.minutes;
    last_hours = current_time.hours;
  }
  // debug(current_time.seconds);
}

void updateTrackTime(void) {
    // if (current_speed > 0) {
      track_time_sec++;
      unsigned char hours = floor(track_time_sec / 3600);
      unsigned char minutes = floor((track_time_sec % 3600) / 60);
      unsigned char seconds = floor((track_time_sec % 3600) % 60);
      char buf[10];
      sprintf(buf,"%02u:%02u:%02u", hours, minutes, seconds);
      nlcd_Text(buf,TRACK_TIME_OFFSET_Y,TRACK_TIME_OFFSET_X,BLACK,WHITE);
  // }
}
//
// void convertTime(Time *time, tm *tm) {
//   tm.tm_sec = time.seconds;
//   tm.tm_min = time.minutes;
//   tm.tm_hour = time.hours;
//   tm.tm_wday = time.day;
//   tm.tm_mday = time.date;
//   tm.tm_mon = time.month;
//   tm.tm_year = time.year + 2000;
//   // debug(current_time_tt);
//   // _delay_ms(400);
// }
