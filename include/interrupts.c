ISR(INT2_vect) {
  if (GLOBAL_INTERRUPT_FLAG) {
    float timer = TCNT1 * 1.0;
    TCNT1 = 0;

    current_speed = 65535.0 / timer * SPEED_MAGIC_NUMBER * 0.036;
    drawRect(0, 90, 132, 42, WHITE);
    debug1(current_speed);
    debug2(timer);
  }
}

ISR(INT0_vect) {
  if (GLOBAL_INTERRUPT_FLAG) {
    updateMainClock();
    // updateTrackTime();
  }
}

ISR(TIMER0_OVF_vect) {
  if (GLOBAL_INTERRUPT_FLAG) {
    if (timer_step < ADC_MAX_STEPS) {
      timer_step++;
    } else {
      timer_step = 0;
    }
  }
}

ISR(ADC_vect) {
  if (GLOBAL_INTERRUPT_FLAG) {
    if (ADC_MODE)
      luminosity = ADCH;
    else
      battery_voltage = ADCH;
    ADC_FREE = 1;
  }
}
