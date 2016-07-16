void showMainScreen(void) {
  // nlcd_Box(0, 0, 131, 131, 1, WHITE);
  drawBattery();
  initSpeedBar();
  // nlcd_Text("Iteration: ",124,10,BLUE,WHITE);
  for (unsigned char i = 0; i < 100; i++) {
    // char str[10];
    // sprintf(str, "%d", i);
    // nlcd_Text(str,124,10 + (11 * 8),BLUE,WHITE);
    drawBatteryCharge(i);
    if ((i + 1) % 10 == 0) {
      drawSpeedBar((i + 1) / 10);
    }
    // _delay_ms(10);
    // timer = TCNT1;
    // timer = -32423;
    // debug1(TCNT1);
  }

  // _delay_ms(200);

  // for (unsigned char i = 99; i > 0; i--) {
  //   char str[10];
  //   sprintf(str, "%d", i);
  //   nlcd_Text(str,124,10 + (11 * 8),BLUE,WHITE);
  //   drawBatteryCharge(i);
  //   if ((i + 1) % 10 == 0) {
  //     drawSpeedBar((i + 1) / 10);
  //   }
  //   _delay_ms(10);
  // }

  // _delay_ms(200);
}

void showSettingScreen(void) {
  // TODO
}

void showScreen(unsigned char screen_mode) {
  switch (screen_mode) {
    case SCREEN_MODE_MAIN:
      showMainScreen();
    default:
      showMainScreen();
  }
}
