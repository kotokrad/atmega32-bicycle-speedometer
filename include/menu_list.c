typedef struct {
  char items[MENU_MAX_ITEMS][16];
  void (*actions[MENU_MAX_ITEMS])(void);
  unsigned char length;
} Menu;

// Settings
void menu_settings_action1(void);
void menu_settings_action2(void);
void menu_settings_action3(void);
void menu_settings_action4(void);

void menu_settings_action1(void) {
  nlcd_Text("Hello",90,10,RED,WHITE);
}
void menu_settings_action2(void) {
  nlcd_Text("Hello",90,10,GREEN,WHITE);
}
void menu_settings_action3(void) {
  nlcd_Text("Hello",90,10,BLUE,WHITE);
}
void menu_settings_action4(void) {
  nlcd_Text("Hello",90,10,BROWN,WHITE);
}

Menu initMenu_settings(void) {
  Menu menu_settings;
  strcpy(menu_settings.items[0], "Foo");
  strcpy(menu_settings.items[1], "Bar");
  strcpy(menu_settings.items[2], "Baz");
  strcpy(menu_settings.items[3], "Boo");

  menu_settings.actions[0] = menu_settings_action1;
  menu_settings.actions[1] = menu_settings_action2;
  menu_settings.actions[2] = menu_settings_action3;
  menu_settings.actions[3] = menu_settings_action4;

  menu_settings.length = 4;

  return menu_settings;
}
// end
