#define SCREEN_MODE_MAIN      1
#define MODE_SETTINGS         2

#define BATTERY_X             104
#define BATTERY_Y             2
#define BATTERY_W             24
#define BATTERY_H             12
#define SPEEDBAR_OFFSET_X     3
#define SPEEDBAR_OFFSET_Y     2
#define SPEEDBAR_COLOR_BG     0xEEE
#define SPEED_MAX             35
#define BATTERY_COLOR_BG      0x333
#define BATTERY_COLOR_100     0x9B3
#define BATTERY_COLOR_30      0x9B3
#define BATTERY_COLOR_15      0x9B3
#define BATTERY_MIN_VOLTAGE   196
#define GRAPH_OFFSET_X        6
#define GRAPH_OFFSET_Y        80
#define GRAPH_GRID_OFFSET_X   5       // GRAPH_OFFSET_X - 1
#define GRAPH_GRID_OFFSET_Y   80      // GRAPH_OFFSET_Y
#define GRAPH_MAX_X           120
#define GRAPH_MAX_Y           48
#define GRAPH_COLOR_THRESHOLD 170
#define MENU_OFFSET_Y         1
#define MENU_OFFSET_X         5
#define MENU_NORMAL_FG        BROWN
#define MENU_NORMAL_BG        WHITE
#define MENU_SELECTED_FG      WHITE
#define MENU_SELECTED_BG      BROWN
#define MENU_MAX_ITEMS        8
#define CLOCK_OFFSET_X        5
#define CLOCK_OFFSET_Y        18
#define TRACK_TIME_OFFSET_X   5
#define TRACK_TIME_OFFSET_Y   50
#define BUTTON_UP             (PINB & (1<<PINB0))
#define BUTTON_DOWN           (PINB & (1<<PINB1))
#define BUTTON_OK             (PINB & (1<<PINB2))
#define SPEED_MAGIC_NUMBER    49.35236
#define ADC_MAX_STEPS         255
#define ADC_CHECK_STEP(x)     !(timer_step % x)
#define ADC_BATTERY_STEP      15 // 255
#define ADC_LUMINOSITY_STEP   63
#define ADC_DEBUG_STEP        16


// Flags
unsigned char GLOBAL_INTERRUPT_FLAG = 0;
unsigned char CYCLE_INTERRUPT_FLAG = 0;
unsigned char ADC_MODE = 0;
unsigned char ADC_FREE = 0;


unsigned char PINS[] = {
  PINB0, // button UP
  PINB1, // buttin DOWN
  PINB3  // button SELECT
};

const unsigned char SPEEDBAR_COORDS[10][2] = {
  {0,51},{1,35},{6,20},{16,8},{31,2},{49,0},{64,2},{77,9},{87,24},{93,44}
};
const int SPEEDBAR_COLORS[10] = {
  0xFC0,0xFC0,0xFC0,0xFC0,0xFC0,0xFC0,0xFC0,0xE32,0xE32,0xE32
};

unsigned char INTERRUPT_COUNTER = 0;

// TODO function signatures
