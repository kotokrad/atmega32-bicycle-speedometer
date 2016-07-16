void drawMenuLine(char text[], unsigned char line, unsigned char selected) {
  int fColor, bColor;
  line = line + 3; // Why? Who knows
  unsigned char x = MENU_OFFSET_X;
  unsigned char y = MENU_OFFSET_Y + (line * 10) - 10;
  unsigned char length = strlen(text);
  if (selected == 0) {
    fColor = MENU_NORMAL_FG;
    bColor = MENU_NORMAL_BG;
    drawRect(MENU_OFFSET_X, y-16-1, 132 - MENU_OFFSET_X * 2, 8 + 3, MENU_NORMAL_BG);
  } else {
    fColor = MENU_SELECTED_FG;
    bColor = MENU_SELECTED_BG;
    drawRect(MENU_OFFSET_X, y-16-1, 132 - MENU_OFFSET_X * 2, 8 + 3, MENU_SELECTED_BG);
  }
  nlcd_Text(text, y, x + 2, fColor, bColor);
}

void drawMenu(Menu menu) {
  unsigned char selected = 0;
  nlcd_Box(0, 0, 131, 131, 1, MENU_NORMAL_BG);
  for (unsigned char i = 0; i < menu.length; i++) {
    if (i == menu_selected_item)
      selected = 1;
    else
      selected = 0;
    drawMenuLine(menu.items[i], i, selected);
  }
  menu_last_item = menu.length - 1;
  memcpy(menu_item_set, menu.items, sizeof(char) * menu.length * 16);
  for (unsigned char i = 0; i < menu.length; i++) {
    menu_action_set[i] = menu.actions[i];
  }
}

void selectMenuItem(unsigned char new_item) {
  if (menu_selected_item != new_item) {
    drawMenuLine(menu_item_set[menu_selected_item], menu_selected_item, 0);
    drawMenuLine(menu_item_set[new_item], new_item, 1);
    menu_selected_item = new_item;
  }
}
