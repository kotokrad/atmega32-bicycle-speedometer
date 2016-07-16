//***************************************************************************
//  File........: Nokia6610_lcd_lib.h
//  Author(s)...: Goncharenko Valery
//  URL(s)......: http://digitalchip.ru
//  Device(s)...: ATMega32
//  Compiler....: Winavr-20100110
//  Description.: ������� LCD Nokia6610 ( ONLY PCF8833 )
//  Data........: 23.07.12
//  Version.....:
//***************************************************************************

#include <avr/io.h>   // ���������� �����-������

//***************************************************************************
// Notice: ��� ����������� �������� LCD-����������� ������ ���� ���������� �
// ������ � ���� �� ����� �� ����������������
//***************************************************************************
// ����, � �������� ��������� LCD ���������� Nokia6610

#define PORT_LCD PORTC
#define PIN_LCD  PINC
#define DDR_LCD  DDRC

// ������ ������� �����, � ������� ���������� ������ LCD-�����������

#define SCLK_LCD_PIN    3
#define SDA_LCD_PIN     2
#define CS_LCD_PIN      5
#define RST_LCD_PIN     4

// ������� ����������� PCF8833

#define LCD_PHILLIPS_NOP        0x00   // nop
#define LCD_PHILLIPS_SWRESET    0x01   // software reset
#define LCD_PHILLIPS_BSTROFF    0x02   // booster voltage OFF
#define LCD_PHILLIPS_BSTRON     0x03   // booster voltage ON
#define LCD_PHILLIPS_RDDIDIF    0x04   // read display identification
#define LCD_PHILLIPS_RDDST      0x09   // read display status
#define LCD_PHILLIPS_SLEEPIN    0x10   // sleep in
#define LCD_PHILLIPS_SLEEPOUT   0x11   // sleep out
#define LCD_PHILLIPS_PTLON      0x12   // partial display mode
#define LCD_PHILLIPS_NORON      0x13   // display normal mode
#define LCD_PHILLIPS_INVOFF     0x20   // inversion OFF
#define LCD_PHILLIPS_INVON      0x21   // inversion ON
#define LCD_PHILLIPS_DALO       0x22   // all pixel OFF
#define LCD_PHILLIPS_DAL        0x23   // all pixel ON
#define LCD_PHILLIPS_SETCON     0x25   // write contrast              1-byte
#define LCD_PHILLIPS_DISPOFF    0x28   // display OFF
#define LCD_PHILLIPS_DISPON     0x29   // display ON
#define LCD_PHILLIPS_CASET      0x2A   // column address set          2-byte
#define LCD_PHILLIPS_PASET      0x2B   // page address set            2-byte
#define LCD_PHILLIPS_RAMWR      0x2C   // memory write
#define LCD_PHILLIPS_RGBSET     0x2D   // colour set                  20-byte
#define LCD_PHILLIPS_PTLAR      0x30   // partial area
#define LCD_PHILLIPS_VSCRDEF    0x33   // vertical scrolling definition
#define LCD_PHILLIPS_TEOFF      0x34   // test mode OFF
#define LCD_PHILLIPS_TEON       0x35   // test mode ON
#define LCD_PHILLIPS_MADCTL     0x36   // memory access control       1-byte
#define LCD_PHILLIPS_SEP        0x37   // vertical scrolling start address
#define LCD_PHILLIPS_IDMOFF     0x38   // idle mode OFF
#define LCD_PHILLIPS_IDMON      0x39   // idle mode ON
#define LCD_PHILLIPS_COLMOD     0x3A   // interface pixel format      1-byte
#define LCD_PHILLIPS_SETVOP     0xB0   // set Vop
#define LCD_PHILLIPS_BRS        0xB4   // bottom row swap
#define LCD_PHILLIPS_TRS        0xB6   // top row swap
#define LCD_PHILLIPS_DISCTR     0xB9   // display control
#define LCD_PHILLIPS_DOR        0xBA   // data order
#define LCD_PHILLIPS_TCDFE      0xBD   // enable/disable DF temperature compensation
#define LCD_PHILLIPS_TCVOPE     0xBF   // enable/disable Vop temp comp
#define LCD_PHILLIPS_EC         0xC0   // internal or external  oscillator
#define LCD_PHILLIPS_SETMUL     0xC2   // set multiplication factor
#define LCD_PHILLIPS_TCVOPAB    0xC3   // set TCVOP slopes A and B
#define LCD_PHILLIPS_TCVOPCD    0xC4   // set TCVOP slopes c and d
#define LCD_PHILLIPS_TCDF       0xC5   // set divider frequency
#define LCD_PHILLIPS_DF8COLOR   0xC6   // set divider frequency 8-color mode
#define LCD_PHILLIPS_SETBS      0xC7   // set bias system
#define LCD_PHILLIPS_RDTEMP     0xC8   // temperature read back
#define LCD_PHILLIPS_NLI        0xC9   // n-line inversion
#define LCD_PHILLIPS_RDID1      0xDA   // read ID1
#define LCD_PHILLIPS_RDID2      0xDB   // read ID2
#define LCD_PHILLIPS_RDID3      0xDC   // read ID3

//**********************************************************************************************
//   ! ����������� ��������, ��� ������� �������� ��� LCD-���������� 0                         *
//   ! � ���������� ������� ������� 8���, Atmega �������� �� 8���  RC-���������                *
//   ! ����������� ��� ���������� ���������� - ������ � ����� LCD ������������� �������� ��    *
#define NLCD_MIN_DELAY	0
//**********************************************************************************************
// ������� � �����������

#define SCLK_LCD_SET    PORT_LCD |= (1<<SCLK_LCD_PIN)
#define SDA_LCD_SET     PORT_LCD |= (1<<SDA_LCD_PIN)
#define CS_LCD_SET      PORT_LCD |= (1<<CS_LCD_PIN)
#define RST_LCD_SET     PORT_LCD |= (1<<RST_LCD_PIN)

#define SCLK_LCD_RESET  PORT_LCD &= ~(1<<SCLK_LCD_PIN)
#define SDA_LCD_RESET   PORT_LCD &= ~(1<<SDA_LCD_PIN)
#define CS_LCD_RESET    PORT_LCD &= ~(1<<CS_LCD_PIN)
#define RST_LCD_RESET   PORT_LCD &= ~(1<<RST_LCD_PIN)

#define CMD_LCD_MODE	0
#define DATA_LCD_MODE	1

#define NOFILL	        0
#define FILL            1

//******************************************************************************
// ��������� ������ ����� ��������: ���.- ����. � �����.    ����. - ������ ����.
// #define FULL_CHARSET
//******************************************************************************
// ������� �����

#define WHITE     0xFFF       // �����
#define BLACK     0x000       // ������
#define RED       0xF00       // �������
#define GREEN     0x0F0       // �������
#define BLUE      0x00F       // �����
#define CYAN      0x1FF       // ���������
#define MAGENTA   0xF0F       // ����������
#define YELLOW    0xFF0       // ������
#define GRAY	    0x222       // �����
#define LIGHTBLUE 0xADE       // ������-�������
#define PINK      0xF6A       // �������
#define BROWN     0xB22       // ����������
#define ORANGE    0xFA0       // ���������

//******************************************************************************
// ��������� �������

// ������������� ������� + ������� ����
void nlcd_Init(void);

// �������� ����� (������� ��� ������) �� LCD-����������
void nlcd_SendByte(char mode,unsigned char c);

// ������������� ������� ���������� x, y � �����������
void nlcd_GotoXY(unsigned char x, unsigned char y);

// ������������� Pixel � ������� x, y, ������ color
void nlcd_Pixel(unsigned char x, unsigned char y, int color);

// ������ ����� �� ���������� x0, y0 � ���������� x1, y1 ������ color
void nlcd_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color);

// ������ ������������� �� ���������� x0, y0 � ���������� x1, y1 � �������� ��� ���, ������ color
void nlcd_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color);

// ������ ���� �� ���������� x0, y0, � �������� (� Pixel), ��� ������� ������ color
void nlcd_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color);

// ������������� ������ � ���������� x, y, ������ fColor, � ����� bColor
void nlcd_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor);

// ������� ����� � ��������� x, y,������ ������ fColor, � ����� bColor
void nlcd_Text(char *the_text, unsigned char x, unsigned char  y,  int fColor, int bColor);

void nlcd_Shape(const unsigned char shape[], unsigned char x, unsigned char y, int color);

// ������� �������� � ��������� x, y (������� ����� ����), ������ �������� �� ����������� � ��������� � ��������, ��� ������� � ���������
void nlcd_Bitmap(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data);
