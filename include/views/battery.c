void drawBattery(void) {
  drawBorder(BATTERY_X, BATTERY_Y, BATTERY_W, BATTERY_H, BATTERY_COLOR_BG);
  drawBorder(BATTERY_X + BATTERY_W, BATTERY_Y + (BATTERY_H / 4), 2, BATTERY_H / 2, BATTERY_COLOR_BG);
  drawBorder(BATTERY_X + 1, BATTERY_Y + 1, BATTERY_W - 2, BATTERY_H - 2, WHITE);
}

void drawBatteryCharge() {
  unsigned char fill_width = ceil(20 * battery_capacity / battery_voltage_diff);
  battery_capacity = battery_voltage - BATTERY_MIN_VOLTAGE;
  if (fill_width != battery_icon_state && fill_width <= 20 && fill_width >= 0) {
    battery_percentage = 100 * battery_capacity / battery_voltage_diff;
    // drawRect(BATTERY_X + 2, BATTERY_Y + 2, BATTERY_W - 4, BATTERY_H - 4, WHITE);
    // drawRect(BATTERY_X + 2, BATTERY_Y + 2, fill_width, BATTERY_H - 4, BATTERY_COLOR_100);
    if (fill_width > battery_icon_state) {
      drawRect(BATTERY_X + battery_icon_state + 2, BATTERY_Y + 2, fill_width - battery_icon_state, BATTERY_H - 4, BATTERY_COLOR_100);
    } else if (fill_width < battery_icon_state) {
      drawRect(BATTERY_X + fill_width + 2, BATTERY_Y + 2, battery_icon_state - fill_width, BATTERY_H - 4, WHITE);
    }
    debug1(fill_width);
    debug3(battery_voltage);
    battery_icon_state = fill_width;
  }
}
