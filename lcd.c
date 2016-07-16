#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "include/lcd.h"
#include "lib/Nokia6610_lcd_lib.c"
#include "lib/ds1307lib.c"

// ===================== UTILS ==========================
#include "include/utils.c"

// ===================== MODEL ==========================
#include "include/model.c"
#include "include/menu_list.c"
#include "include/graphics/speedbar_array.c"

// ===================== VIEW ===========================
// SpeedBar
#include "include/views/speedbar.c"
// Battery
#include "include/views/battery.c"
// Graph
#include "include/views/graph.c"
// Menu
#include "include/views/menu.c"
// Screen mode
#include "include/views/screenmode.c"
// Clock
#include "include/views/time.c"
// ===================== CONTROLLER =====================
// Menu actions
// #include "include/controllers/menu_actions.c"
// Button actions
#include "include/controllers/button_actions.c"
// Button press handler
#include "include/controllers/button_handler.c"
// Menu
// #include "include/controllers/menu.c"
// ADC
#include "include/adc.c"


// ======================== INIT ========================
#include "include/init.c"
#include "include/interrupts.c"
// ===================== MAIN LOOP ======================

int main(void)
{
  init();

  // MENU EXAMPLE
  // Menu menu_settings = initMenu_settings();
  // drawMenu(menu_settings);

  // BATTERY EXAMPLE
  drawBattery();

  while(1)
  {
    adc_check();
    // debug2(battery_voltage);
    // drawBatteryCharge();
    // _delay_ms(10);
    debugText("HELLO WORLD");
    _delay_ms(1000);

















    // // Читаем данные и преобразуем из BCD в двоичную систему
    // DS1307_Read(0x00,&time_temp); // Чтение регистра секунд
    // time_second = (((time_temp & 0xF0) >> 4)*10)+(time_temp & 0x0F);
    // DS1307_Read(0x01,&time_temp); // Чтение регистра минут
    // time_minute = (((time_temp & 0xF0) >> 4)*10)+(time_temp & 0x0F);
    // DS1307_Read(0x02,&time_temp); // Чтение регистра часов
    // time_hour = (((time_temp & 0xF0) >> 4)*10)+(time_temp & 0x0F);

    // if (time_last_second != time_second || time_last_minute != time_minute || time_last_hour != time_hour) {
    //   sprintf(buf,"%02d:%02d:%02d",time_hour,time_minute,time_second);
    //   debugText(buf);
    //   time_last_second = time_second;
    //   time_last_minute = time_minute;
    //   time_last_hour = time_hour;
    // }
    // _delay_ms(300);
    // debugX(current_time.seconds);
    // sprintf(buf,"%02d:%02d:%02d", current_time.hours, current_time.minutes, current_time.seconds);
    // sprintf(buf,"%02d:%02d:%02d",current_time[2],current_time[1],current_time[0]);
    // debugText("               ");
    // debugText(buf);
    // debugX(current_time[0]);


    // debugText("       ");
    // debug(saved);
    // _delay_ms(500);
    // I2C_StartCondition();
    // TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    // while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
    // debugText("      ");
    // debug(TWCR);
    // _delay_ms(500);

    // I2C_SendByte(DS1307_ADDR_R);
    // TWDR = DS1307_ADDR_R;//загрузка значения в регистр данных
    // debugText("       ");
    // debug(TWDR);
    // _delay_ms(500);
    // TWCR = saved;
    // TWCR = (1<<TWINT)|(1<<TWEN);//начаало передачи байта данных
    // while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
    // debugText("      ");
    // debug(TWCR);
    // _delay_ms(500);

    // for (size_t i = 0; i < 6; i++) {
    //   debugText("      ");
    //   debug(I2C_RecieveByte());
    //   _delay_ms(500);
    // }
    // debugText("      ");
    // debug(I2C_RecieveLastByte());
    // _delay_ms(500);

    // I2C_StopCondition();
    // TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    // debugText("      ");
    // debug(TWCR);
    // _delay_ms(500);

    // sprintf(buf,"time: %02d:%02d:%02d",ds1307_Time.hours,ds1307_Time.minutes,ds1307_Time.seconds);
    // debugText(buf);
    // _delay_ms(1200);
    // debugText("----------------");
    // _delay_ms(400);


    // nlcd_Box(0, 0, 131, 131, 1, BLACK);
    // drawGraph();
    // showMainScreen();

    // listenButtons(b_actions_menu);





    // Мусор, пригодится
    // nlcd_Pixel(20,46,GREEN);
    // nlcd_Char('W',40,12,WHITE,BLACK);
    // nlcd_Text("HELLO",20,50,GREEN,BLACK);
    // nlcd_Bitmap (20, 0, 65, 132, bitmap_data_1);
    // nlcd_Line(20, 24, 40, 44, YELLOW);
  }
}
