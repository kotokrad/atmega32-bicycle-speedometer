void drawSpeedBarSection(unsigned char number, unsigned char state) {
  unsigned char x = SPEEDBAR_COORDS[number][0] + SPEEDBAR_OFFSET_X;
  unsigned char y = SPEEDBAR_COORDS[number][1] + SPEEDBAR_OFFSET_Y;
  int color;
  if (state)
  color = SPEEDBAR_COLORS[number];
  else
  color = SPEEDBAR_COLOR_BG;
  nlcd_Shape(speedbar[number], y, x, color);
}

void initSpeedBar(void) {
  speedbar_state = 10;
  drawSpeedBar(1);
}

void drawSpeedBar(unsigned char number) {
  number--;
  speedbar_state--;
  unsigned char start, end, i;
  if (number > speedbar_state) {
    start = speedbar_state + 1;
    end = number;
    for (i = start; i <= end; i++) {
      drawSpeedBarSection(i, 1);
      speedbar_state = number;
    }
  } else if (number < speedbar_state) {
    start = number;
    end = speedbar_state;
    for (i = start; i <= end; i++) {
      drawSpeedBarSection(i, 0);
      speedbar_state = number;
    }
  } else {
    return;
  }
}
