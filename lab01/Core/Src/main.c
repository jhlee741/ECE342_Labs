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
#include "config.h"
#include <stdio.h>


int8_t current_row = -1, current_col = -1;
int8_t char_index = 0;
char char_table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};
char message[100];

int main(void)
{
  /* Reset of all peripherals. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();

  
  sprintf(message, "Printing test ");
  print_msg(message);

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  
  /* Initialize ROW outputs */
  HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);

  /* Infinite loop */
  while (1)
  {
    HAL_GPIO_TogglePin(ROW0_GPIO_Port, ROW0_Pin);//toggle pin high
		current_row=0;
		HAL_Delay(1);
		HAL_GPIO_TogglePin(ROW0_GPIO_Port, ROW0_Pin);//toggle pin low
		//current_row=-1;
		HAL_Delay(1);
		
		HAL_GPIO_TogglePin(ROW1_GPIO_Port, ROW1_Pin);
		current_row=1;
		HAL_Delay(1);
		HAL_GPIO_TogglePin(ROW1_GPIO_Port, ROW1_Pin);
		//current_row=-1;
		HAL_Delay(1);
		
		HAL_GPIO_TogglePin(ROW2_GPIO_Port, ROW2_Pin);
		current_row=2;
		HAL_Delay(1);
		HAL_GPIO_TogglePin(ROW2_GPIO_Port, ROW2_Pin);
		//current_row=-1;
		HAL_Delay(1);
		
		HAL_GPIO_TogglePin(ROW3_GPIO_Port, ROW3_Pin);
		current_row=3;
		HAL_Delay(1);
		HAL_GPIO_TogglePin(ROW3_GPIO_Port, ROW3_Pin);
		//current_row=-1;
    HAL_Delay(1); //small delay between iterations
		
		message[0]=char_table[char_index];
		message[1]='\0';
		print_msg(message);
  }
}