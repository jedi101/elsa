/**
******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system_init.h"
#include "display/DisplaySSD1306.h"

char text_eLSA[] = "eLSA";
char text_welcome[] = "Welcome!";
char text_running[] = "Running";
char text_progress_left[] = "<<<";
char text_progress_right[] = ">>>";

/* main function -------------------------------------------------------------*/
int main(void)
{

	/*initialize mcu system and peripherals*/
	msp_system_init();

	eLSA::DISPLAY::Display_SSD1306* display = new eLSA::DISPLAY::Display_SSD1306(&hi2c1, 0x3C << 1);

	display->setCursor(30, 20);
	display->writeString(text_eLSA, eLSA::DISPLAY::Font_16x26, eLSA::DISPLAY::White);
	//display->setCursor(15, 25);
	//display->writeString("Evomation", eLSA::Font_11x18, eLSA::White);
	display->updateScreen();
	HAL_Delay(2000);
	display->fill(eLSA::DISPLAY::Black);
	display->setCursor(20, 25);
	display->writeString(text_welcome, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::White);
	display->updateScreen();
	HAL_Delay(2000);

	/* Infinite loop */
	while (1)
	{
		for(int i = 0; i<5; i++){
			display->fill(eLSA::DISPLAY::Black);
			display->setCursor(20, 5);
			display->writeString(text_running, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::White);
		  	display->setCursor((35 + (i*5)), 30);
		  	display->writeString(text_progress_right, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::White);
		  	display->updateScreen();
		  	HAL_Delay(750);
		}

		for(int i = 0; i<5; i++){
			display->fill(eLSA::DISPLAY::Black);
			display->setCursor(20, 5);
			display->writeString(text_running, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::White);
			display->setCursor((50 - (i*5)), 30);
			display->writeString(text_progress_left, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::White);
			display->updateScreen();
			HAL_Delay(750);
		}

	}
}
