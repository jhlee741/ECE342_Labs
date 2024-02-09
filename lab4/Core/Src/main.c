/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "main.h"

#include "dfr0151.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//RTC Variables
uint8_t *week_day;
uint8_t *day;
uint8_t *month;
uint8_t *year;
uint8_t *hour;
uint8_t *min;
uint8_t *sec;

//EEPROM VARIABLES
uint8_t *dates;
uint8_t *times;

//Interrupt variable
volatile int8_t interrupt_trigger;

int main(void)
{
  /* Reset of all peripherals. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();  
  rtc_init();

  char message[100];

  // Your start up code here
	times = (uint8_t*) malloc(7 * sizeof(uint8_t));

	sec = (uint8_t*) malloc(sizeof(uint8_t));
	min = (uint8_t*) malloc(sizeof(uint8_t));
	hour = (uint8_t*) malloc(sizeof(uint8_t));


	week_day = (uint8_t*) malloc(sizeof(uint8_t));
	day = (uint8_t*) malloc(sizeof(uint8_t));
	month = (uint8_t*) malloc(sizeof(uint8_t));
	year = (uint8_t*) malloc(sizeof(uint8_t));
	
	
	interrupt_trigger = 0;
	for (int i=0; i<7; i++){
		times[i]=eeprom_read(i);
		HAL_Delay(20);
		
	}
	sprintf(message, "Stored time: \n");
	print_msg(message);
	sprintf(message, "Weekday: %d, Day: %d, Month: %d, Year: %d\n", times[3], times[4], times[5], times[6]);
	print_msg(message);

	sprintf(message, "Hour: %d, Min: %d, Sec: %d \n", times[2], times[1], times[0]);
	print_msg(message);
	rtc_set_time(times[0], times[1], times[2]);
	rtc_set_date(times[3], times[4], times[5], times[6]);
	
	uint8_t test=50;

  while (1){
		
		if (interrupt_trigger==1){
			for (int i=0; i<7; i++){
				eeprom_write(i,&times[i], 1);
				HAL_Delay(20);
			}
			eeprom_write(6, &test, 1);
			HAL_Delay(20);
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			interrupt_trigger=0;
		}
		
		rtc_get_date(week_day,day,month,year);
		rtc_get_time(hour, min, sec);
		

		sprintf(message, "RTC Time: ");
		print_msg(message);

		sprintf(message, "Weekday: %d, Day: %d, Month: %d, Year: %d\n", times[3], times[4], times[5], times[6]);
		print_msg(message);

		sprintf(message, "Hour: %d, Min: %d, Sec: %d \n", times[2], times[1], times[0]);
		print_msg(message);

		HAL_Delay(500); 

  }
}
