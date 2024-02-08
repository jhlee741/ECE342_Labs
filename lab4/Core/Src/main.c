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

  char msg[100];
	sprintf(msg, "Startup\n");
	print_msg(msg);
  // Your start up code here
	uint8_t hour, min, sec, week_day, month, year, day;
	uint8_t time_arr[3];
	uint8_t test=9+5;

  while (1)
  {
		/*
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    HAL_Delay(500);
    print_msg("\b\b\b\btick");

    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    HAL_Delay(500);
    print_msg("\b\b\b\btock"); */
		
		rtc_get_date(&week_day, &day, &month, &year);
		rtc_get_time(&hour, &min, &sec);
		HAL_I2C_Mem_Read(&hi2c1,ADDR_DS1307,0x0,I2C_MEMADD_SIZE_8BIT,time_arr,3,100);
		HAL_I2C_Mem_Write(&hi2c1,ADDR_DS1307,0x0,I2C_MEMADD_SIZE_8BIT,&test,1,100);
		
		sprintf(msg, "Sec: %d, Min: %d, Hr: %d\n", time_arr[0], time_arr[1], time_arr[2]);
		//sprintf(msg, "Year: %d, Month: %d, Day: %d, Weekday: %d, Hour: %d, Min: %d, Sec: %d\n", year, month, day, week_day, hour, min, sec);
		print_msg(msg);
		HAL_Delay(500);
  }
}