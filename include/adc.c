void adc_battery(void) {
  if (ADC_FREE) {
    ADC_FREE = 0;
    ADMUX = 0b11100000;
    ADC_MODE = 0;
    // ADCSRA = (1<<ADSC);
    ADCSRA = 0b11001111;
  }
}

void adc_luminosity(void) {
  if (ADC_FREE) {
    ADC_FREE = 0;
    ADMUX = 0b11100001;
    ADC_MODE = 1;
    // ADCSRA = (1<<ADSC);
    ADCSRA = 0b11001111;
  }
}

void adc_debug(void) {
  // debug1(battery_percentage);
  // debug2(battery_capacity);
  // debug3(battery_voltage);
}

void adc_check(void) {
  // debug3(ADC_LUMINOSITY_STEP);
  if        (ADC_CHECK_STEP(ADC_BATTERY_STEP)) {
    adc_battery();
  } else if (ADC_CHECK_STEP(ADC_LUMINOSITY_STEP)) {
    adc_luminosity();
  } else if (ADC_CHECK_STEP(ADC_DEBUG_STEP)) {
    adc_debug();
  }
}
