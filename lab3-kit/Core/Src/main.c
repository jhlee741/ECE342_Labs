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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "fixedpt.h"

#define PI 3.14159265
/**
  * @brief  The application entry point.
  * @retval int
  */
double sinLUT[628];
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  MX_USART3_Init();
		
	//Enable the timer
	HAL_TIM_Base_Start(&htim6);
	__HAL_TIM_SET_PRESCALER(&htim6,99);
	
	//DAC Enable
	HAL_DAC_Init(&hdac);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	
	double time_final;
	double time_start;
	double time_end;
	volatile double sin_value;
	volatile int sum = 0;
	int test;
	
	char message[100];
	//double *sinLUT=(double*)malloc(628*sizeof(double));
	
	double n=0;
	for(int i = 0; i < 628; i += 1){
		sinLUT[i]=2000*(1+ sin(n));
		n+=0.01;
		sprintf(message, "Sinval: %f\n", sinLUT[i]);
		print_msg(message);
	}
	
/*
	sprintf(message, "Hello");
	print_msg(message); */
	
	int iterator = 0;
	
  while (1)
  {
		/* Part 1 
		time_start = __HAL_TIM_GET_COUNTER(&htim6);
		
		for(int i = 0; i < 1000; i++){
			sum = sum + i;
		}
		sum=0;
		
		time_end = __HAL_TIM_GET_COUNTER(&htim6);
	  time_final = time_end - time_start;
		
		sprintf(message, "Time elapsed: %f	\n", time_final);
		print_msg(message); */
		
	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		
		/* sin wave
		time_start = __HAL_TIM_GET_COUNTER(&htim6);
		for(volatile double i = 0; i < 2*PI; i += 0.01){
			sin_value = 2000*(1+ sin(i));
			//sprintf(message, "Sin(%f): %d	\n", i, (int)sin_value);
			//print_msg(message);
			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (int)sin_value);
		}
		time_end = __HAL_TIM_GET_COUNTER(&htim6);
	  time_final = time_end - time_start; */
		
		/* //sin wave LUT
		time_start = __HAL_TIM_GET_COUNTER(&htim6);
		for(int i = 0; i < 628; i += 1){
			
			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (int)sinLUT[i]);
			//sprintf(message, "LUT val: %f	\n", sinLUT[i]);
			//print_msg(message);
			//HAL_Delay(1);
		}
		
		time_end = __HAL_TIM_GET_COUNTER(&htim6);
	  time_final = time_end - time_start; 
		
		sprintf(message, "Time elapsed: %f	\n", time_final);
		print_msg(message); */
		
		//HAL_Delay(1000);
		
		//Generating arbitrary waveforms
		float temp = 0;

		/*if(iterator > 628) {
			break; 
    } 
		else {
			temp = (float) (sinLUT[iterator % 628]+5)*0.5* pow(2,10); // -> will generate perfect sine wave 
    }*/
		
		for(int harmonic = 1; harmonic < 200; harmonic += 2){
			temp += (float) (sinLUT[(harmonic * iterator) % 628]+5)* 4/(PI * harmonic) * pow(2,10); // will generate square wave 
    }
		
		/*for(int harmonic = 1; harmonic < 50; harmonic++){
			temp += (float) (sinLUT[(harmonic * iterator) % 628]+ 4)* 1/(harmonic) * pow(2,9); //will generate sawtooth
    } */
		
		 /*for(int harmonic = 1; harmonic < 100; harmonic += 2){
			temp += (float) (sinLUT[(harmonic * iterator) % 628] + 2)* pow(-1, ((harmonic - 1)/2))/pow(harmonic, 2) * pow(2, 9); // will generate triangular wave
     }*/


		//sprintf(message, "temp value: %f	\n", temp);
		//print_msg(message);

		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (int)temp);
    iterator++;
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  } 
	
	//free(sinLUT);
}
