void initScreen(void) {
  nlcd_Init();
  nlcd_Box(0, 0, 131, 131, 1, WHITE);
}


void initButtons(void) {
  b_actions_main[0] = b_action_redtext;
  b_actions_main[1] = b_action_greentext;
  b_actions_main[2] = b_action_bluetext;

  b_actions_menu[0] = b_action_up;
  b_actions_menu[1] = b_action_down;
  b_actions_menu[2] = b_action_select;
}

void initRTC(void) {
  I2CInit();
  DS1307_Write(0x07, 0b00010000);
  updateMainClock();
  // struct Time start_time;
  // struct tm start_time_tm;
  // DS1307GetTime(&start_time);
  // start_time_tm.tm_sec = current_time.seconds;
  // start_time_tm.tm_min = current_time.minutes;
  // start_time_tm.tm_hour = current_time.hours;
  // start_time_tm.tm_wday = current_time.day;
  // start_time_tm.tm_mday = current_time.date;
  // start_time_tm.tm_mon = current_time.month;
  // start_time_tm.tm_year = current_time.year + 2000;
  // start_time_tt = mk_gmtime(&current_time_tm);
}

void init(void) {
  asm("cli");
  // ports
  DDRB = 0b00000000;
  PORTB = 0b00001111;
  DDRD = 0b00000000;
  PORTD = 0b00000100;
  // interrupts
  MCUCSR = (1<<ISC2);
  GICR = (1<<INT2);
  GICR = (1<<INT0);
  // timer 1
  TCCR1A = 0x00;
  TCCR1B = 0b00000101;
  // timer 0
  TCCR0 = 0b00001101;
  OCR0 = 0xFF;
  TIMSK = 0b00000001; // ??
  // ADC
  ADCSRA = 0b10001111; //(1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
  ADC_FREE = 1;
  adc_battery();
  adc_luminosity();



  initScreen();
  initButtons();
  initRTC();

  GLOBAL_INTERRUPT_FLAG = 1;
  asm("sei");
}
