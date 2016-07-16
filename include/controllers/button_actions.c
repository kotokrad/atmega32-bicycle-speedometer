// main screen
void (*b_actions_main[3]) (void); // Массив указателей функций - действий для кнопок.
void b_action_redtext(void);
void b_action_greentext(void);
void b_action_bluetext(void);

void b_action_redtext(void) {
  nlcd_Text("Hello",90,10,RED,WHITE);
}

void b_action_greentext(void) {
  nlcd_Text("Hello",90,10,GREEN,WHITE);
}

void b_action_bluetext(void) {
  nlcd_Text("Hello",90,10,BLUE,WHITE);
}

// menu screen
void (*b_actions_menu[3]) (void); // Массив указателей функций - действий для кнопок.
void b_action_up(void);
void b_action_down(void);
void b_action_select(void);

void b_action_up(void) {
  if (menu_selected_item > 0) {
    selectMenuItem(menu_selected_item - 1);
  } else {
    selectMenuItem(menu_last_item);
  }
}

void b_action_down(void) {
  if (menu_selected_item < menu_last_item) {
    selectMenuItem(menu_selected_item + 1);
  } else {
    selectMenuItem(0);
  }
}

void b_action_select(void) {
  (menu_action_set[menu_selected_item])();
  // b_action_bluetext();
}
