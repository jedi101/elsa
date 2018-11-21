/**
******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system_init.h"

/* main function -------------------------------------------------------------*/
int main(void)
{

	/*initialize mcu system and peripherals*/
	msp_system_init();

	/* Infinite loop */
	while (1)
	{
	  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
	  HAL_Delay(1000);
	}
}
