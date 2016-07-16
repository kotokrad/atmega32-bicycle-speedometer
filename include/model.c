unsigned char screen_mode = SCREEN_MODE_MAIN;
unsigned char menu_selected_item = 1;
unsigned char menu_last_item = 0;
char menu_item_set[MENU_MAX_ITEMS][16];
void (*menu_action_set[MENU_MAX_ITEMS]) (void);
unsigned char speedbar_state = 0;
float current_speed = 0;
float max_speed = 0;
float avg_speed = 0;
int current_distance = 0;
int total_distance = 0;
unsigned long track_time_sec = 184221;
struct Time current_time;
unsigned char last_seconds, last_minutes, last_hours;
unsigned char battery_voltage = 0;
unsigned char battery_capacity = 0;
unsigned char battery_percentage = 0;
unsigned char battery_voltage_diff = 255 - BATTERY_MIN_VOLTAGE;
unsigned char battery_icon_state = 0;
unsigned char luminosity = 0;

unsigned char timer_step = 0;







unsigned char speed_array[120] = {
  0, 3, 11, 16, 20, 22, 24, 27,
  29, 31, 32, 33, 33, 32, 31, 31,
  30, 28, 27, 25, 24, 22, 21, 15,
  16, 16, 20, 24, 26, 28, 31, 33,
  33, 33, 33, 33, 33, 32, 29, 27,
  25, 23, 22, 22, 22, 23, 23, 24,
  25, 25, 26, 27, 29, 31, 32, 31,
  31, 31, 31, 31, 30, 28, 27, 25,
  24, 24, 26, 28, 29, 30, 31, 32,
  32, 31, 27, 23, 18, 15, 13, 11,
  9, 9, 14, 22, 31, 37, 40, 40,
  37, 35, 34, 30, 23, 16, 13, 14,
  14, 14, 12, 11, 15, 22, 27, 32,
  34, 34, 33, 33, 32, 30, 26, 21,
  16, 13, 12, 11, 12, 14, 15, 17,
};

int speed_current(void) {
  return 20;
}

int speed_average(void) {
  return 16;
}
