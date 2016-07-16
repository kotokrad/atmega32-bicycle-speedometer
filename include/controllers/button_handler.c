void checkButton(unsigned char button, void (*callback) (void)) {
  if (!(PINB & (1<<PINS[button]))) {
    _delay_ms(10);
    (*callback)();
    while (!(PINB & (1<<PINS[button])));
    // waitButtonRelease(button);
  }
}

// void waitButtonRelease(unsigned char button) {
//   while (!(PINB & (1<<PINS[button]))) {
//     _delay_ms(50);
//   }
// }

void listenButtons(void (*actionset[3])()) {
  for (unsigned char i = 0; i < 3; i++) {
    checkButton(i, actionset[i]);
  }
}
