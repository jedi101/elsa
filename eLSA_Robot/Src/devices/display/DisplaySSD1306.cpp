/*
 * Display_SSD1306.c
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#include "display/DisplaySSD1306.h"
#include <cstring>
#include <exception>

namespace eLSA {
namespace display {

DisplaySSD1306::DisplaySSD1306(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress)
	:_i2cPort{i2cPort}, _i2cAddress{deviceAddress}
{
	if(_i2cPort && _i2cAddress) {

		//retrieve new i2c interface object
		_i2cInterface = new comDevices::StmI2cDevice(_i2cPort, _i2cAddress);

		if(_i2cInterface) {

			//set display standard timeout for i2c device
			_i2cInterface->setConnectionTimeout(DISPLAY_SSD1306_I2C_TIMEOUT);

			// Init OLED by writing all commands in ssd1306InitCommands
			for(unsigned int i = 0; i < (sizeof(ssd1306InitCommands)/sizeof(ssd1306InitCommands[0])); i++)
			{
				_writeI2cCommand(ssd1306InitCommands[i]);
			}

			// Clear screen
			fill(Black);

			// Flush buffer to screen
			updateScreen();

			// Set default values for screen object
			_screenObject.CurrentX = 0;
			_screenObject.CurrentY = 0;

			_screenObject.Initialized = 1;
		}
	}
}

DisplaySSD1306::~DisplaySSD1306()
{
	delete _i2cInterface;
}

/*public methods*/

// fill the whole display with one color
void DisplaySSD1306::fill(Color_t color)
{
	/* Set complete screen to one color */
	uint32_t i;

	for(i = 0; i < sizeof(_screenBuffer); i++) {
		_screenBuffer[i] = (color == Black) ? 0x00 : 0xFF;;
	}
}

// update the screen after set commands
void DisplaySSD1306::updateScreen(void) {
    uint8_t i;
    for(i = 0; i < 8; i++) {
    	_writeI2cCommand(0xB0 + i);
    	_writeI2cCommand(0x00);
    	_writeI2cCommand(0x10);
    	_writeI2cData(&_screenBuffer[DISPLAY_SSD1306_WIDTH*i],DISPLAY_SSD1306_WIDTH);
    }
}

//draw single pixel to display
void DisplaySSD1306::drawPixel(uint8_t x, uint8_t y, Color_t color) {
    if(x >= DISPLAY_SSD1306_WIDTH || y >= DISPLAY_SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }

    // Check if pixel should be inverted
    if(_screenObject.Inverted) {
        color = (Color_t)!color;
    }

    // Draw in the right color
    if(color == White) {
    	_screenBuffer[x + (y / 8) * DISPLAY_SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
    	_screenBuffer[x + (y / 8) * DISPLAY_SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

//write character to display
char DisplaySSD1306::writeChar(char ch, FontDef_t Font, Color_t color) {
    uint32_t i, b, j;

    // Check remaining space on current line
    if (DISPLAY_SSD1306_WIDTH <= (_screenObject.CurrentX + Font.fontWidth) ||
    		DISPLAY_SSD1306_HEIGHT <= (_screenObject.CurrentY + Font.fontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.fontHeight; i++) {
        b = Font.data[(ch - 32) * Font.fontHeight + i];
        for(j = 0; j < Font.fontWidth; j++) {
            if((b << j) & 0x8000)  {
            	drawPixel(_screenObject.CurrentX + j, (_screenObject.CurrentY + i), (Color_t) color);
            } else {
            	drawPixel(_screenObject.CurrentX + j, (_screenObject.CurrentY + i), (Color_t)!color);
            }
        }
    }

    // The current space is now taken
    _screenObject.CurrentX += Font.fontWidth;

    // Return written char for validation
    return ch;
}

// Write full string to screenbuffer
char DisplaySSD1306::writeString(char* str, FontDef_t Font, Color_t color) {
    // Write until null-byte
    while (*str) {
        if (writeChar(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }

        // Next char
        str++;
    }

    // Everything ok
    return *str;
}

// Position the cursor
void DisplaySSD1306::setCursor(uint8_t x, uint8_t y) {
	_screenObject.CurrentX = x;
	_screenObject.CurrentY = y;
}

// test the possible screen refresh rate
void DisplaySSD1306::testFps(void) {
	fill(White);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";
    char initText[] = "Testing...";

    setCursor(2,0);
    writeString(initText, Font_11x18, Black);

    //write chars for 5 seconds
    do {
    	setCursor(2, 18);
    	writeString(message, Font_11x18, Black);
    	updateScreen();

        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        //count shown frames
        fps++;
        end = HAL_GetTick();
    } while((end - start) < 5000);

    //calculate and show frame rate
    char buff[64];
    fps = (float)fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);

    fill(White);
    setCursor(2, 18);
    writeString(buff, Font_11x18, Black);
    updateScreen();
}

/* private methods*/

// write a I2C command to the controller
void DisplaySSD1306::_writeI2cCommand(uint8_t command)
{
	try {
		_i2cInterface->setDeviceRegisterParams(DISPLAY_SSD1306_I2C_COMMAND_REGISTER, DISPLAY_SSD1306_I2C_ADDRESS_LENGTH);
	} catch(...) {
		throw;
	}

	try {
		_i2cInterface->writeData(&command, DISPLAY_SSD1306_I2C_COMMAND_LENGTH);
	} catch(...) {
		throw;
	}
}

// write data via I2C to the display
void DisplaySSD1306::_writeI2cData(uint8_t* p_data, uint16_t data_size)
{
	try {
		_i2cInterface->setDeviceRegisterParams(DISPLAY_SSD1306_I2C_DATA_REGISTER, DISPLAY_SSD1306_I2C_ADDRESS_LENGTH);
	} catch(...) {
		throw;
	}

	try {
		_i2cInterface->writeData(p_data, data_size);
	} catch(...) {
		throw;
	}

}

} /* namespace display*/
} /* namespace eLSA*/

