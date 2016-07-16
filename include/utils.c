#define joinColors(R, G, B)    ((int)(R & 0xF0) << 4 ) | (G & 0xF0) | ((B & 0xF0) >> 4)

void drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, int color) {
  if (w > 0 && h > 0) {
    nlcd_Box(y, x, y + h - 1, x + w - 1, 1, color);
  }
}

void drawBorder(unsigned char x, unsigned char y, unsigned char w, unsigned char h, int color) {
  if (w > 0 && h > 0) {
    nlcd_Box(y, x, y + h - 1, x + w - 1, 0, color);
  }
}

// int joinColors(unsigned char R, unsigned char G, unsigned char B) {
//   return ((int)(R & 0xF0) << 4 ) | (G & 0xF0) | ((B & 0xF0) >> 4);
// }

void debug(long var) {
  char result[10];
  sprintf(result, "%u", var);
  nlcd_Text(result,124,10,BLACK,WHITE);
}

void debug1(unsigned char var) {
  char result[10];
  sprintf(result, "%0.3d", var);
  nlcd_Text(result,104,10,BLACK,WHITE);
}

void debug2(unsigned char var) {
  char result[10];
  sprintf(result, "%0.3u", var);
  nlcd_Text(result,114,10,BLACK,WHITE);
}

void debug3(unsigned char var) {
  char result[10];
  sprintf(result, "%0.3u", var);
  nlcd_Text(result,124,10,BLACK,WHITE);
}

void debugX(int var) {
  char result[10];
  sprintf(result, "0x%X", var);
  nlcd_Text(result,124,10,BLACK,WHITE);
}

void debugText(char text[]) {
  nlcd_Text(text,94,10,BLACK,WHITE);
}
