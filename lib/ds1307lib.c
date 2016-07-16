//адрес микросхемы DS1307
#define DS1307_ADDR  0b01101000
//адрес микросхемы DS1307 + бит чтения
#define DS1307_ADDR_R  (DS1307_ADDR<<1)|1
//адрес микросхемы DS1307 + бит записи
#define DS1307_ADDR_W   DS1307_ADDR<<1

#define DS1307_number_to_ds(x)    (((x & 0xF0) >> 4)*10)+(x & 0x0F)

// Функция инициализация шины TWI
void I2CInit(void)
{
  // настройка TWI модуля
  TWBR = 2;
  TWSR = (1 << TWPS1)|(1 << TWPS0); // Предделитель на 64
  TWCR |= (1 << TWEN); // Включение модуля TWI
}

void I2CStart(void)
{
  // Передача условия СТАРТ
  TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTA);
  // Ожидание установки флага TWINT
  while(!(TWCR & (1 << TWINT)));
}

void I2CStop(void)
{
  TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); // Передача условия СТОП
  while(TWCR & (1 << TWSTO)); // Ожидание завершения передачи условия СТОП
}

// Функция записи данных по шине
uint8_t I2CWriteByte(uint8_t data)
{
  TWDR = data; // Загрузка данных в TWDR
  TWCR = (1 << TWEN)|(1 << TWINT); // Сброс флага TWINT для начала передачи данных
  while(!(TWCR & (1 << TWINT))); // Ожидание завершения передачи
  // Проверка статуса
  if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
  {
    // Если адрес DS1307, биты R/W и данные переданы
    // и получено подтверждение
    return 1;
  }
  else
  return 0; // ОШИБКА
}

// Функция чтения данных по шине
uint8_t I2CReadByte(uint8_t *data,uint8_t ack)
{
  if(ack) // Устанавливаем подтверждение
  {
    // Возвращаем подтверждение после приема
    TWCR |= (1 << TWEA);
  }
  else
  {
    // Возвращаем неподтверждение после приема
    // Ведомое устройство не получает больше данных
    // обычно используется для распознования последнего байта
    TWCR &= ~(1 << TWEA);
  }
  // Разрешение приема данных после сброса TWINT
  TWCR |= (1 << TWINT);
  while(!(TWCR & (1 << TWINT))); // Ожидание установки флага TWINT
  // Проверка статуса
  if((TWSR & 0xF8) == 0x58 || (TWSR & 0xF8) == 0x50)
  {
    // Прием данных и возвращение подтверждения
    //	или
    // Прием данных и возвращение неподтверждения
    *data = TWDR; // Читаем данные
    return 1;
  }
  else
  return 0; // Ошибка
}
// Функция чтения данных из DS1307
uint8_t DS1307_Read(uint8_t address,uint8_t *data)
{
  uint8_t res; // Результат
  I2CStart(); // СТАРТ
  res = I2CWriteByte(DS1307_ADDR_W);	// адрес DS1307 + бит W
  if(!res)	return 0; // ОШИБКА
  // Передача адреса необходимого регистра
  res = I2CWriteByte(address);
  if(!res)	return 0; // ОШИБКА
  I2CStart(); // Повторный СТАРТ
  res = I2CWriteByte(DS1307_ADDR_R);	// адрес DS1307 + бит R
  if(!res)	return 0; // ОШИБКА
  // Чтение данных с неподтверждением
  res = I2CReadByte(data,0);
  if(!res)	return 0; // ОШИБКА
  I2CStop(); // СТОП
  return 1;
}
// Функция записи данных в DS1307
uint8_t DS1307_Write(uint8_t address,uint8_t data)
{
  uint8_t res; // Результат
  I2CStart();	// СТАРТ
  res = I2CWriteByte(DS1307_ADDR_W);	// адрес DS1307 + бит W
  if(!res)	return 0; // ОШИБКА
  // Передача адреса необходимого регистра
  res = I2CWriteByte(address);
  if(!res)	return 0; // ОШИБКА
  res = I2CWriteByte(data); // Запись данных
  if(!res)	return 0; // ОШИБКА
  I2CStop(); // СТОП
  return 1;
}

// ----------------------------------------

//описание структуры времени
struct Time
{
  char seconds;  //секунды
  char minutes;  //минуты
  char hours;    //часы
  char day;      //день недели
  char date;     //число
  char month;    //месяц
  int year;      //год
};

int DS1307GetTime(struct Time* ds) { //
  uint8_t res; // Результат
  unsigned char byte;
  // unsigned char temp, data;
  // char buf[10];
  I2CStart(); // СТАРТ
  res = I2CWriteByte(DS1307_ADDR_W);	// адрес DS1307 + бит W
  if(!res)	return 0; // ОШИБКА
  // Передача адреса необходимого регистра
  res = I2CWriteByte(0x00);
  if(!res)	return 0; // ОШИБКА

  I2CStart(); // СТАРТ
  res = I2CWriteByte(DS1307_ADDR_R);	// адрес DS1307 + бит R
  if(!res)	return 0;
  // I2CReadByte(&temp,0);
  // sprintf(buf,"seconds: %02d",DS1307_number_to_ds(temp));
  // debugText(buf);
  // DS1307_Read(0x01, &temp);
  // debugText(buf);
  // _delay_ms(300);

  // Чтение данных (последний байт с неподтверждением)
  I2CReadByte(&byte,1);
  // array[0] = DS1307_number_to_ds(byte);
  ds->seconds = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,1);
  // array[1] = DS1307_number_to_ds(byte);
  ds->minutes = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,1);
  // array[2] = DS1307_number_to_ds(byte);
  ds->hours = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,1);
  ds->day = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,1);
  ds->date = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,1);
  ds->month = DS1307_number_to_ds(byte);
  I2CReadByte(&byte,0);
  ds->year = DS1307_number_to_ds(byte);
  // res = I2CReadByte(data,0);
  // if(!res) return 0; // ОШИБКА
  // DS1307_convert_to_ds(ds);
  I2CStop(); // СТОП
  return 1;
}
