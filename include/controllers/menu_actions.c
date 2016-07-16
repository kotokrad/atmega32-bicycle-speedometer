void action1(void);
void action2(void);
void action3(void);
void action4(void);
void (*m_actions_settings[4]) (void); // Массив указателей функций - действий в меню.

void action1(void) {
  nlcd_Text("Hello",90,10,RED,WHITE);
}

void action2(void) {
  nlcd_Text("Hello",90,10,GREEN,WHITE);
}

void action3(void) {
  nlcd_Text("Hello",90,10,BLUE,WHITE);
}

void action4(void) {
  nlcd_Text("Hello",90,10,BROWN,WHITE);
}

// void doAction(unsigned char number) {
//   (func[number])();
// }
