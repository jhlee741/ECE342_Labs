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
#include <math.h>

#define PI 3.14

int main(void)
{
  /* Reset of all peripherals. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC3_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_DAC_Init();

  uint16_t adc_res, dac_out, mask = 0xff00; //c=1100
	uint16_t freqs[5]={10000, 0,0,0,0};
	uint16_t sin_outs[5]={0,0,0,0,0};
  char message[100]="Hello";
	print_msg(message);
  
  //  ADC example
  HAL_ADC_Start(&hadc3);
  HAL_ADC_PollForConversion(&hadc3, 100);
  adc_res = HAL_ADC_GetValue(&hadc3);
  sprintf(message, "adc_res=%d\r\n", adc_res);
  print_msg(message);
  
  // DAC example
  HAL_DAC_Init(&hdac);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 255);
	
	uint32_t start_time=HAL_GetTick();
	float step=PI/freqs[0];
	float arg=0;
  while (1)
  {
		/* //Part 1,2,3
		HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3, 10);
    adc_res = HAL_ADC_GetValue(&hadc3);
		adc_res=adc_res&mask;
		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, adc_res);
		*/
		
		//part 4
		//float arg=(HAL_GetTick()-start_time)*freqs[0]/1000;
		
		arg+=step;
		/*
		while (arg>2*PI){
			arg-=2*PI;
		}*/
		
		dac_out=2000*sin(arg);
		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_out);
		//sprintf(message, "dacout=%f\r\n",arg);
		//print_msg(message);
  }
 }