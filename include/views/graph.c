void drawGraphLine(unsigned char line_x, unsigned char height, int color) {
  unsigned char x = GRAPH_OFFSET_X + line_x;
  unsigned char y = GRAPH_OFFSET_Y + GRAPH_MAX_Y - height;
  // nlcd_Pixel(y,x,color);
  // nlcd_Pixel(y+1,x,color);
  // nlcd_Pixel(y+2,x,color);
  nlcd_Line(y, x, GRAPH_OFFSET_Y + GRAPH_MAX_Y, x, color);
  nlcd_Line(y, x + 1, GRAPH_OFFSET_Y + GRAPH_MAX_Y, x + 1, color);
  nlcd_Line(y, x + 2, GRAPH_OFFSET_Y + GRAPH_MAX_Y, x + 2, color);
}

void drawGraphGrid(void) {
  for (unsigned char i = 0; i < GRAPH_MAX_X; i += 12) {
    unsigned char x = GRAPH_GRID_OFFSET_X + i;
    unsigned char y1 = GRAPH_GRID_OFFSET_Y;
    unsigned char y2 = GRAPH_GRID_OFFSET_Y + GRAPH_MAX_Y;
    nlcd_Line(y1, x, y2, x, 0xDDD);
  }
  for (unsigned char i = 0; i < GRAPH_MAX_Y; i += 12) {
    unsigned char x1 = GRAPH_GRID_OFFSET_X;
    unsigned char x2 = GRAPH_GRID_OFFSET_X + GRAPH_MAX_X;
    unsigned char y = GRAPH_GRID_OFFSET_Y + i;
    nlcd_Line(y, x1, y, x2, 0xDDD);
  }
  drawBorder(GRAPH_GRID_OFFSET_X, GRAPH_GRID_OFFSET_Y, GRAPH_MAX_X + 2, GRAPH_MAX_Y + 2, 0xAAA);
}

void drawGraph(void) {
  drawGraphGrid();
  for (unsigned char i = 0; i < GRAPH_MAX_X; i++) {
    unsigned char r, g, range, cutted_level;
    unsigned char value = speed_array[i];
    unsigned char level = round(value * 100 / GRAPH_MAX_Y * 255 / 100);
    if (level > GRAPH_COLOR_THRESHOLD) {
      range = 255 - GRAPH_COLOR_THRESHOLD;
      cutted_level = level - GRAPH_COLOR_THRESHOLD;
      r = 255;
      g = 255 - round(cutted_level * 100 / range * 255 / 100);
    } else {
      range = GRAPH_COLOR_THRESHOLD;
      cutted_level = level;
      r = round(cutted_level * 100 / range * 255 / 100);
      g = 255;
    }

    int color = joinColors(r, g, 0);


    // TODO fix skipping
    drawGraphLine(i, value, color);
    i += 3;
  }
}
