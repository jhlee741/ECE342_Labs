#include "dfr0151.h"

extern I2C_HandleTypeDef hi2c1;


uint8_t bcd2bin(uint8_t data){
 return ((data >> 4) * 10) + (data & 0x0F);
}

uint8_t bin2bcd(uint8_t data){
  return ((data / 10) << 4)|(data % 10);
}

uint8_t rtc_read(uint8_t address)
{
  uint8_t data;

  if (HAL_I2C_Mem_Read(&hi2c1,ADDR_DS1307,address,I2C_MEMADD_SIZE_8BIT,&data,1,100) != HAL_OK) {
    Error_Handler();
  }

  return data;
}

void rtc_write(uint8_t address,uint8_t data)
{
  if (HAL_I2C_Mem_Write(&hi2c1,ADDR_DS1307,address,I2C_MEMADD_SIZE_8BIT,&data,1,100) != HAL_OK){
    Error_Handler();
  }
}

void rtc_init()
{
  // Initialize Real-Time Clock peripheral
  uint8_t rs=0, sqwe=1, out=0;
  
  rs&=3;
  if (sqwe) rs|=0x10;
  if (out) rs|=0x80;

  rtc_write(0x07,rs);
	
	uint8_t ch = rtc_read(0x00);
	ch &= ~(1 << 7);
	rtc_write(0x00, ch);
}

void rtc_get_time(uint8_t *hour,uint8_t *min,uint8_t *sec)
{
  // Your code here
	*hour = rtc_read(0x2);
	*min = rtc_read(0x1);
	*sec = rtc_read(0x0);
	
	return;
	
}

void rtc_set_time(uint8_t hour,uint8_t min,uint8_t sec)
{
  // Your code here
	rtc_write(hour,0x2);
	rtc_write(min,0x1);
	rtc_write(sec,0x0);
}

void rtc_get_date(uint8_t *week_day,uint8_t *day,uint8_t *month,uint8_t *year)
{
  // Your code here
	*week_day = rtc_read(0x3);
	*day = rtc_read(0x4);
	*month = rtc_read(0x5);
	*year = rtc_read(0x6);
	
	return;
}

void rtc_set_date(uint8_t week_day,uint8_t day,uint8_t month,uint8_t year)
{
  // Your code here
	rtc_write(week_day,0x3);
	rtc_write(day,0x4);
	rtc_write(month,0x5);	
	rtc_write(year,0x6);	
}

void eeprom_write(uint16_t address, uint8_t *data, uint16_t size) {
  // Your code here
}

uint8_t eeprom_read(uint16_t address) {
  // Your code here
  return -1;
}