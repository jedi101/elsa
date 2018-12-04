/*
 * Display_SSD1306.c
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#include "display/DisplaySSD1306.h"
#include <cstring>

eLSA::DISPLAY::Display_SSD1306::Display_SSD1306(I2C_HandleTypeDef* i2c_port, uint16_t device_address)
	:_i2c_port{i2c_port}, _i2c_address{device_address}
{
	if(i2c_port && device_address) {

		//retrieve new i2c interface object
		_i2c_interface = new eLSA::STM_I2C_Device(_i2c_port, _i2c_address);

		if(_i2c_interface) {

			//set display standard timeout for i2c device
			_i2c_interface->setConnectionTimeout(DISPLAY_SSD1306_I2C_TIMEOUT);

			// Init OLED
			_writeI2cCommand(0xAE); //display off
			_writeI2cCommand(0x20); //Set Memory Addressing Mode
			_writeI2cCommand(0x10); // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode;
									  // 10,Page Addressing Mode (RESET); 11,Invalid
			_writeI2cCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
			_writeI2cCommand(0xC8); //Set COM Output Scan Direction
			_writeI2cCommand(0x00); //---set low column address
			_writeI2cCommand(0x10); //---set high column address
			_writeI2cCommand(0x40); //--set start line address - CHECK
			_writeI2cCommand(0x81); //--set contrast control register - CHECK
			_writeI2cCommand(0xFF);
			_writeI2cCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
			_writeI2cCommand(0xA6); //--set normal color
			_writeI2cCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
			_writeI2cCommand(0x3F); //
			_writeI2cCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
			_writeI2cCommand(0xD3); //-set display offset - CHECK
			_writeI2cCommand(0x00); //-not offset
			_writeI2cCommand(0xD5); //--set display clock divide ratio/oscillator frequency
			_writeI2cCommand(0xF0); //--set divide ratio
			_writeI2cCommand(0xD9); //--set pre-charge period
			_writeI2cCommand(0x22); //
			_writeI2cCommand(0xDA); //--set com pins hardware configuration - CHECK
			_writeI2cCommand(0x12);
			_writeI2cCommand(0xDB); //--set vcomh
			_writeI2cCommand(0x20); //0x20,0.77xVcc
			_writeI2cCommand(0x8D); //--set DC-DC enable
			_writeI2cCommand(0x14); //
			_writeI2cCommand(0xAF); //--turn on SSD1306 panel

			// Clear screen
			fill(Black);

			// Flush buffer to screen
			updateScreen();

			// Set default values for screen object
			screen_object.CurrentX = 0;
			screen_object.CurrentY = 0;

			screen_object.Initialized = 1;
		}
	}
}

eLSA::DISPLAY::Display_SSD1306::~Display_SSD1306()
{
	delete _i2c_interface;
}

/*public methods*/

// fill the whole display with one color
void eLSA::DISPLAY::Display_SSD1306::fill(DISPLAY_SSD1306_COLOR color)
{
	/* Set complete screen to one color */
	uint32_t i;

	for(i = 0; i < sizeof(screenBuffer); i++) {
		screenBuffer[i] = (color == eLSA::DISPLAY::Black) ? 0x00 : 0xFF;;
	}
}

// update the screen after set commands
void eLSA::DISPLAY::Display_SSD1306::updateScreen(void) {
    uint8_t i;
    for(i = 0; i < 8; i++) {
    	_writeI2cCommand(0xB0 + i);
    	_writeI2cCommand(0x00);
    	_writeI2cCommand(0x10);
    	_writeI2cData(&screenBuffer[DISPLAY_SSD1306_WIDTH*i],DISPLAY_SSD1306_WIDTH);
    }
}

//draw single pixel to display
void eLSA::DISPLAY::Display_SSD1306::drawPixel(uint8_t x, uint8_t y, DISPLAY_SSD1306_COLOR color) {
    if(x >= DISPLAY_SSD1306_WIDTH || y >= DISPLAY_SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }

    // Check if pixel should be inverted
    if(screen_object.Inverted) {
        color = (DISPLAY_SSD1306_COLOR)!color;
    }

    // Draw in the right color
    if(color == White) {
    	screenBuffer[x + (y / 8) * DISPLAY_SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
    	screenBuffer[x + (y / 8) * DISPLAY_SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

//write character to display
char eLSA::DISPLAY::Display_SSD1306::writeChar(char ch, FontDef Font, DISPLAY_SSD1306_COLOR color) {
    uint32_t i, b, j;

    // Check remaining space on current line
    if (DISPLAY_SSD1306_WIDTH <= (screen_object.CurrentX + Font.FontWidth) ||
    		DISPLAY_SSD1306_HEIGHT <= (screen_object.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
            	drawPixel(screen_object.CurrentX + j, (screen_object.CurrentY + i), (DISPLAY_SSD1306_COLOR) color);
            } else {
            	drawPixel(screen_object.CurrentX + j, (screen_object.CurrentY + i), (DISPLAY_SSD1306_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    screen_object.CurrentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}

// Write full string to screenbuffer
char eLSA::DISPLAY::Display_SSD1306::writeString(char* str, FontDef Font, DISPLAY_SSD1306_COLOR color) {
    // Write until null-byte
    while (*str) {
        if (eLSA::DISPLAY::Display_SSD1306::writeChar(*str, Font, color) != *str) {
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
void eLSA::DISPLAY::Display_SSD1306::setCursor(uint8_t x, uint8_t y) {
	screen_object.CurrentX = x;
	screen_object.CurrentY = y;
}

// test the possible screen refresh rate
void eLSA::DISPLAY::Display_SSD1306::testFps(void) {
	fill(eLSA::DISPLAY::White);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";
    char initText[] = "Testing...";

    setCursor(2,0);
    writeString(initText, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);

    //write chars for 5 seconds
    do {
    	setCursor(2, 18);
    	writeString(message, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);
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

    fill(eLSA::DISPLAY::White);
    setCursor(2, 18);
    writeString(buff, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);
    updateScreen();
}

/* private methods*/

// write a I2C command to the controller
unsigned int eLSA::DISPLAY::Display_SSD1306::_writeI2cCommand(uint8_t command)
{
	_i2c_interface->setDeviceRegisterParams(DISPLAY_SSD1306_I2C_COMMAND_REGISTER, DISPLAY_SSD1306_I2C_ADDRESS_LENGTH);
	return _i2c_interface->writeData(&command, DISPLAY_SSD1306_I2C_COMMAND_LENGTH);
}

// write data via I2C to the display
unsigned int eLSA::DISPLAY::Display_SSD1306::_writeI2cData(uint8_t* p_data, uint16_t data_size)
{
	_i2c_interface->setDeviceRegisterParams(DISPLAY_SSD1306_I2C_DATA_REGISTER, DISPLAY_SSD1306_I2C_ADDRESS_LENGTH);
	return _i2c_interface->writeData(p_data, data_size);
}


