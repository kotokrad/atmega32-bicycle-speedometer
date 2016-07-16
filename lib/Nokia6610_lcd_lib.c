//***************************************************************************
//  File........: Nokia6610_lcd_lib.c
//  Author(s)...: Goncharenko Valery
//  URL(s)......: http://digitalchip.ru
//  Device(s)...: ATMega32
//  Compiler....: Winavr-20100110
//  Description.: ������� LCD Nokia6610 ( ONLY PCF8833 )
//  Data........: 23.07.12
//  Version.....:
//******************************************************************************

#include "Nokia6610_lcd_lib.h"
#include <util/delay.h>             // ���������� ����������
#include "Nokia6610_fnt8x8.h"
// #include "robo1_font.h"

//******************************************************************************

void nlcd_Init(void)   //  ������������� ����������� PCF8833
{
  //  �������������� ���� �� ����� ��� ������ � LCD-������������
  DDR_LCD |= (1<<SCLK_LCD_PIN)|(1<<SDA_LCD_PIN)|(1<<CS_LCD_PIN)|(1<<RST_LCD_PIN);

  CS_LCD_RESET;
  SDA_LCD_RESET;
  SCLK_LCD_SET;

  RST_LCD_SET;       //     **********************************************
  RST_LCD_RESET;    //     *                                             *
  _delay_ms(20);   //     *  �������� ��� ��������� ���������� ������   *
  RST_LCD_SET;      //     *                                             *
  _delay_ms(20);    //     **********************************************
  SCLK_LCD_SET;
  SDA_LCD_SET;
  SCLK_LCD_SET;

  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_SWRESET);   //    ����������� �����
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_SLEEPOUT);  //    ����� �� ������ ���
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_BSTRON);    //    ���. ���������� ��������������� ����������
  _delay_ms(10);                                      //    �������� ��� ��������� ������� � ������������ ����������
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_DISPON);    //    ������� ���.
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NORON);     //    ������� ���������� - ���.
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_PASET);     //    ��������� ���������� � ��������� ������ �������
  nlcd_SendByte(DATA_LCD_MODE,0);                     //
  nlcd_SendByte(DATA_LCD_MODE,0x83);                  //
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_CASET);     //     ��������� ���������� � ��������� ������ ��������
  nlcd_SendByte(DATA_LCD_MODE,0);                     //
  nlcd_SendByte(DATA_LCD_MODE,0x83);                  //
  _delay_ms(5);
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_RAMWR);     //     ������ ������ � RAM �������
  _delay_ms(50);                                      //     ������� ����
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_INVOFF);    //    �������� ������ ������ - ���������
  //    ******************************************************
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_COLMOD);    //   *               ����� �����:                          *
  nlcd_SendByte(DATA_LCD_MODE,0x03);                  //  *     12 ��� �� �������- 4096 ������ RGB 3:3:2          *
  //  **********************************************************
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_MADCTL);    //    ������� ������� � �������� ����������� ������ RAM
  nlcd_SendByte(DATA_LCD_MODE,0x00);                  //   1-byte, �� ��������� 0�00 - ����� ����������� �������
  //                �� ���. 43
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_SETCON);   //            �������������
  nlcd_SendByte(DATA_LCD_MODE,0x2D);                 //         0x00-min   0x3F-max
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_DISPOFF);  //     ��������� ������� ����� �� ��������� ����� �� ������
  nlcd_Box(0, 0, 131, 131, 1, BLACK);                //    �������� ���� ������� ������� ����� - ����� ������� �����
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_DISPON);   //     ������� ���.
}

//******************************************************************************
//  �������� ����� (������� ��� ������) �� LCD-����������
//  mode: CMD_LCD_MODE  - �������� �������
//      DATA_LCD_MODE - �������� ������
//  c:    �������� ������������� �����
void nlcd_SendByte(char mode,unsigned char c)
{
  asm("cli");
  CS_LCD_RESET;
  SCLK_LCD_RESET;
  if(mode) SDA_LCD_SET;
  else     SDA_LCD_RESET;

  SCLK_LCD_SET;

  for(unsigned char i=0;i<8;i++)
  {
    SCLK_LCD_RESET;
    if(c & 0x80) SDA_LCD_SET;
    else       SDA_LCD_RESET;
    SCLK_LCD_SET;
    c <<= 1;
    _delay_us(NLCD_MIN_DELAY);
  }

  CS_LCD_SET;
  if (GLOBAL_INTERRUPT_FLAG)
    asm("sei");
}

//******************************************************************************
//  ���:      GotoXY(unsigned char x, unsigned char y)
//   ��������:    ������������� � ������� x, y
//              GotoXY( x, y)
//  ���������:   x: ������� 0-131
//           y: ������� 0-131
//  ������:     GotoXY(32,17);
//******************************************************************************
void nlcd_GotoXY(unsigned char x, unsigned char y)
{
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_PASET);   // ������� ������ �������� RAM
  nlcd_SendByte(DATA_LCD_MODE,x);                   // �����
  nlcd_SendByte(DATA_LCD_MODE,x);                   // �����

  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_CASET);   // ������� ������ ������� RAM
  nlcd_SendByte(DATA_LCD_MODE,y);                   // �����
  nlcd_SendByte(DATA_LCD_MODE,y);                   // �����
}

//******************************************************************************
//  ���:      nlcd_Pixel(unsigned char x, unsigned char y, int color)
//   ��������:    ������������� Pixel � ������� x, y, ������ color
//              nlcd_Pixel( x, y,color)
//  ���������:   x:     ������� 0-131
//           y:     ������� 0-131
//               color: ���� (12-bit ��. #define)
//  ������:     nlcd_Pixel(21,45,BLACK);
//******************************************************************************
void nlcd_Pixel(unsigned char x, unsigned char y, int color)
{
  nlcd_GotoXY(x,y);
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_RAMWR);
  CS_LCD_RESET;

  nlcd_SendByte(DATA_LCD_MODE,(color >> 4) & 0xFF );
  nlcd_SendByte(DATA_LCD_MODE,((color & 0xF) << 4) | ((color >> 8) & 0xF) );
  nlcd_SendByte(DATA_LCD_MODE,color & 0xFF);

  CS_LCD_SET;
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NOP);
}

//******************************************************************************
//  ���:      nlcd_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color)
//   ��������:    ������ ����� �� ���������� x0, y0 � ���������� x1, y1 ������ color
//              nlcd_Line(x0, y0, x1, y1, color)
//  ���������:   x:     ������� 0-131
//           y:     ������� 0-131
//               color: ���� (12-bit ��. #define)
//  ������:     nlcd_Line(25,60,25,80,RED);
//******************************************************************************
void nlcd_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color)
{

  int dy = y1 - y0;
  int dx = x1 - x0;
  int stepx, stepy;
  if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
  if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }

  dy <<= 1;                              // dy is now 2*dy
  dx <<= 1;                              // dx is now 2*dx


  nlcd_Pixel(x0, y0, color);

  if (dx > dy)
  {
    int fraction = dy - (dx >> 1);     // same as 2*dy - dx
    while (x0 != x1)
    {
      if (fraction >= 0)
      {
        y0 += stepy;
        fraction -= dx;            // same as fraction -= 2*dx
      }
      x0 += stepx;
      fraction += dy;                // same as fraction -= 2*dy
      nlcd_Pixel(x0, y0, color);
    }
  }
  else
  {
    int fraction = dx - (dy >> 1);
    while (y0 != y1)
    {
      if (fraction >= 0)
      {
        x0 += stepx;
        fraction -= dy;
      }
      y0 += stepy;
      fraction += dx;
      nlcd_Pixel(x0, y0, color);
    }
  }

}

//******************************************************************************
//  ���:      nlcd_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color)
//   ��������:    ������ ������������� �� ���������� x0, y0 � ���������� x1, y1 � �������� ��� ���, ������ color
//              nlcd_Line(x0, y0, x1, y1, fill, color)
//  ���������:   x:     ������� 0-131
//           y:     ������� 0-131
//               fill:  1-� ��������, 0-��� �������
//               color: ���� (12-bit ��. #define)
//  ������:     nlcd_Box(20,30,40,50,1,RED);  // � ��������
//******************************************************************************

void nlcd_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color)
{
  unsigned char   xmin, xmax, ymin, ymax;
  int   i;
  if (fill == FILL)                                   //  ******************************************************
  {                                                   //  * ��������� - ����� ������������� � �������� ��� ���  *              *
    xmin = (x0 <= x1) ? x0 : x1;                   //  * � ����� ���������� 2 ������� �� 1 ����              *
    xmax = (x0 > x1) ? x0 : x1;                    //  *����������� �������� � ������� ��� X � Y             *
    ymin = (y0 <= y1) ? y0 : y1;                   //  *******************************************************
    ymax = (y0 > y1) ? y0 : y1;
    //    *****************************************************
    nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_PASET);    //   *            ���������� ������ � RAM                 *
    nlcd_SendByte(DATA_LCD_MODE,xmin);                 //   *  ��������� ������� �������������� � ������������   *
    nlcd_SendByte(DATA_LCD_MODE,xmax);                 //   *             � ��������� ���������                  *
    nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_CASET);    //   *            ���������� ������� � RAM                *
    nlcd_SendByte(DATA_LCD_MODE,ymin);                 //   *                                                    *
    nlcd_SendByte(DATA_LCD_MODE,ymax);                 //   ******************************************************

    nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_RAMWR);    //        ����� � RAM
    //
    //      ���� ��� ������ ���������� �������� / 2
    //
    for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1))/2 )+1 ); i++)
    {

      // ���������� �������� ����� ��� ������ 3 ������ ������ - ���������� 2 �������
      CS_LCD_RESET;
      nlcd_SendByte(DATA_LCD_MODE,(color >> 4) & 0xFF );
      nlcd_SendByte(DATA_LCD_MODE,((color & 0xF) << 4) | ((color >> 8) & 0xF) );
      nlcd_SendByte(DATA_LCD_MODE,color & 0xFF);
      CS_LCD_SET;
    }
    nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NOP);
  }
  else
  {
    nlcd_Line(x0, y0, x1, y0, color);               //������ ������ ����� ��������������
    nlcd_Line(x0, y1, x1, y1, color);
    nlcd_Line(x0, y0, x0, y1, color);
    nlcd_Line(x1, y0, x1, y1, color);
  }
}

//******************************************************************************
//  ���:      nlcd_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color)
//   ��������:    ������ ���� �� ���������� x0, y0, � �������� � ������ color
//              nlcd_Circle(x0, y0, radius, color)
//  ���������:   x:       ������� 0-131
//           y:       ������� 0-131
//               radius:  � ��������
//               color: ���� (12-bit ��. #define)
//  ������:     nlcd_Circle(10,55,2,BLUE);
//******************************************************************************
void nlcd_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color)
{
  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  unsigned char x = 0;
  unsigned char y = radius;

  nlcd_Pixel(x0, y0 + radius, color);
  nlcd_Pixel(x0, y0 - radius, color);
  nlcd_Pixel(x0 + radius, y0, color);
  nlcd_Pixel(x0 - radius, y0, color);

  while (x < y)
  {
    if (f >= 0)
    {

      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x + 1;

    nlcd_Pixel(x0 + x, y0 + y, color);
    nlcd_Pixel(x0 - x, y0 + y, color);
    nlcd_Pixel(x0 + x, y0 - y, color);
    nlcd_Pixel(x0 - x, y0 - y, color);
    nlcd_Pixel(x0 + y, y0 + x, color);
    nlcd_Pixel(x0 - y, y0 + x, color);
    nlcd_Pixel(x0 + y, y0 - x, color);
    nlcd_Pixel(x0 - y, y0 - x, color);

  }
}

//******************************************************************************
//  ���:     nlcd_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor)
//   ��������:   ������� ������ � ������� x,y, ������ fcolor, � ����� bcolor
//  ���������:  x:       ������� 0-131
//          y:       ������� 0-131
//         fcolor:       ���� (12-bit ��. #define)
//         bcolor:       ���� (12-bit ��. #define)
//  ������:
//******************************************************************************

void nlcd_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor)
{
  int    i;
  int    j;
  unsigned int    nCols;
  unsigned int    nRows;
  unsigned int    nBytes;
  unsigned char   PixelRow;
  unsigned char   Mask;
  unsigned int    Word0;
  unsigned char   *pFont;
  unsigned char   *pChar;

  if (c>127) c=c-64;                // ��������� ������� �������� � ������ ������
  // �������� ������� (������� � ���� 0x80).  ������� Chipper-� �� ��������� !

   pFont = (unsigned char *)Nokia6610_fnt8x8;
  // pFont = (unsigned char *)Robo1_font;

  nCols = pgm_read_byte(pFont);

  nRows = pgm_read_byte(pFont + 1);

  nBytes = pgm_read_byte(pFont + 2);

  pChar = pFont + (nBytes * (c - 0x1F));

  for (i = 0; i<nCols; i++)
  {
    // PixelRow = pgm_read_byte(pChar+9);
    // Mask = 0x80;
    // for (j = 0; j < nRows; j += 1)
    // {
    //   if ((PixelRow & Mask) == 0)
    //   Word0 = bColor;
    //   else
    //   Word0 = fColor;
    //   nlcd_Pixel(x - j , y + i, Word0);
    //   Mask = Mask >> 1;
    // }
    PixelRow = pgm_read_byte(pChar++);
    Mask = 0x80;
    for (j = 0; j < nRows; j += 1)
    {
      if ((PixelRow & Mask) == 0)
      Word0 = bColor;
      else
      Word0 = fColor;
      nlcd_Pixel(x - 8 - j, y + i, Word0);
      Mask = Mask >> 1;
    }
  }
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NOP);
}

//******************************************************************************
//  ���:     nlcd_Text(char *ptext, unsigned char x, unsigned char  y,  int fColor, int bColor)
//   ��������:   ������� ����� � ��������� x, y, ������ fColor, �� ���� bColor
//  ���������:  x:       ������� 0-131
//          y:       ������� 0-131
//              fColor:  ���� (12-bit ��. #define)
//              bColor:  ���� (12-bit ��. #define)
//  ������:    nlcd_Text("Hello",40,12,WHITE,BLACK);
//******************************************************************************
void nlcd_Text(char *ptext, unsigned char x, unsigned char  y,  int fColor, int bColor)
{
  while (*ptext != 0x00)
  {
    nlcd_Char(*ptext++, x, y, fColor, bColor);
    y=y+8;
    if (x > 131) break;
  }
}

//******************************************************************************
//  ���:     nlcd_Shape(unsigned char begin, unsigned char x, unsigned char y, int fColor, int bColor)
//   ��������:   ������� ������ � ������� x,y, ������ fcolor, � ����� bcolor
//  ���������:  x:       ������� 0-131
//          y:       ������� 0-131
//         fcolor:       ���� (12-bit ��. #define)
//         bcolor:       ���� (12-bit ��. #define)
//  ������:
//******************************************************************************

void nlcd_Shape(const unsigned char shape[], unsigned char x, unsigned char y, int color)
{
  int    i;
  int    j;
  int     t;
  unsigned int    nCols;
  unsigned int    nRows;
  unsigned char   PixelRow;
  unsigned char   Mask;
  unsigned char   *pFont;
  unsigned char   *pChar;
  unsigned int    step;

  pFont = (unsigned char *)shape;

  nCols = pgm_read_byte(pFont);

  nRows = pgm_read_byte(pFont + 1);

  pChar = pFont + 2;
  step = 0;
  for (t = 0; t < ceil(nRows / 8); t++) {
    step = step + 8;
    for (i = 0; i<nCols; i++)
    {
      PixelRow = pgm_read_byte(pChar++);
      Mask = 0x80;
      for (j = 0; j < 8; j++)
      {
        if ((PixelRow & Mask) != 0)
        nlcd_Pixel(x + step - j , y + i, color);
        Mask = Mask >> 1;
      }
    }
  }
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NOP);
}

//******************************************************************************
//  ���:      nlcd_Bitmap(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data)
//   ��������:    ������� ����������� � ������� x, y,( ������� ����� ����), � ������� �� ����������� � ��������� ( � ��������),��� ������� � ������������
//  ���������:   x:            ������� 0-131
//               y:            ������� 0-131
//               h_size:       ������� 0-131
//               v_size:       ������� 0-131
//  ������:      nlcd_Bitmap (41, 41, 50 , 50, bitmap_data);
//******************************************************************************
//
//                          �������� !
//  ������� ����������� ������ ���� ������� � ������������ � ��������������� ������, �.�. ���� ��
//  ����������� ������������� �� .jpeg 1600�768 � 100�100 .bmp - ������� h_size � v_size ������ ����
//  ������� ��� 100 � 100 (��������). ����� ����������� ����� ��������� �����������.
//
//******************************************************************************
void nlcd_Bitmap(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data)
{
  int i;
  unsigned char *pBitmap;
  // ������� ������� ������� � ������������ � ����� ���������
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_PASET);   // ������� ������ �������� RAM
  nlcd_SendByte(DATA_LCD_MODE,start_x);             // �����
  nlcd_SendByte(DATA_LCD_MODE,start_x+h_size-1);    // �����

  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_CASET);   // ������� ������ ������� RAM
  nlcd_SendByte(DATA_LCD_MODE,start_y);             // �����
  nlcd_SendByte(DATA_LCD_MODE,start_y+v_size-1);    // �����

  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_RAMWR);   // ����� � RAM

  pBitmap = (unsigned char *)bitmap_data;

  for (i = 0; i< (h_size*v_size)>>1  ; i++)
  {
    unsigned char bitmap;
    CS_LCD_RESET;
    bitmap = pgm_read_byte(pBitmap++);
    nlcd_SendByte(DATA_LCD_MODE,bitmap);
    bitmap = pgm_read_byte(pBitmap++);
    nlcd_SendByte(DATA_LCD_MODE,bitmap);
    bitmap = pgm_read_byte(pBitmap++);
    nlcd_SendByte(DATA_LCD_MODE,bitmap);
    CS_LCD_SET;
  }
  nlcd_SendByte(CMD_LCD_MODE,LCD_PHILLIPS_NOP);
}
