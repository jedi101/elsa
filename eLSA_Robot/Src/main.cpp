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
  /* Infinite loop */
  msp_system_init();

  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
	  HAL_Delay(1000);
  }
}
