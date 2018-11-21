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

		_i2c_interface = new eLSA::STM_I2C_Device(_i2c_port, _i2c_address);

		// Init OLED
		_write_i2c_command(0xAE); //display off
		_write_i2c_command(0x20); //Set Memory Addressing Mode
		_write_i2c_command(0x10); // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode;
								  // 10,Page Addressing Mode (RESET); 11,Invalid
		_write_i2c_command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
		_write_i2c_command(0xC8); //Set COM Output Scan Direction
		_write_i2c_command(0x00); //---set low column address
		_write_i2c_command(0x10); //---set high column address
		_write_i2c_command(0x40); //--set start line address - CHECK
		_write_i2c_command(0x81); //--set contrast control register - CHECK
		_write_i2c_command(0xFF);
		_write_i2c_command(0xA1); //--set segment re-map 0 to 127 - CHECK
		_write_i2c_command(0xA6); //--set normal color
		_write_i2c_command(0xA8); //--set multiplex ratio(1 to 64) - CHECK
		_write_i2c_command(0x3F); //
		_write_i2c_command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
		_write_i2c_command(0xD3); //-set display offset - CHECK
		_write_i2c_command(0x00); //-not offset
		_write_i2c_command(0xD5); //--set display clock divide ratio/oscillator frequency
		_write_i2c_command(0xF0); //--set divide ratio
		_write_i2c_command(0xD9); //--set pre-charge period
		_write_i2c_command(0x22); //
		_write_i2c_command(0xDA); //--set com pins hardware configuration - CHECK
		_write_i2c_command(0x12);
		_write_i2c_command(0xDB); //--set vcomh
		_write_i2c_command(0x20); //0x20,0.77xVcc
		_write_i2c_command(0x8D); //--set DC-DC enable
		_write_i2c_command(0x14); //
		_write_i2c_command(0xAF); //--turn on SSD1306 panel

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

eLSA::DISPLAY::Display_SSD1306::~Display_SSD1306()
{
	delete _i2c_interface;
}

/*public methods*/
void eLSA::DISPLAY::Display_SSD1306::fill(DISPLAY_SSD1306_COLOR color)
{
	/* Set complete screen to one color */
	uint32_t i;

	for(i = 0; i < sizeof(screenBuffer); i++) {
		screenBuffer[i] = (color == eLSA::DISPLAY::Black) ? 0x00 : 0xFF;;
	}
}

void eLSA::DISPLAY::Display_SSD1306::updateScreen(void) {
    uint8_t i;
    for(i = 0; i < 8; i++) {
        _write_i2c_command(0xB0 + i);
        _write_i2c_command(0x00);
        _write_i2c_command(0x10);
        _write_i2c_data(&screenBuffer[DISPLAY_SSD1306_WIDTH*i],DISPLAY_SSD1306_WIDTH);
    }
}

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
            	eLSA::DISPLAY::Display_SSD1306::drawPixel(screen_object.CurrentX + j, (screen_object.CurrentY + i), (DISPLAY_SSD1306_COLOR) color);
            } else {
            	eLSA::DISPLAY::Display_SSD1306::drawPixel(screen_object.CurrentX + j, (screen_object.CurrentY + i), (DISPLAY_SSD1306_COLOR)!color);
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

void eLSA::DISPLAY::Display_SSD1306::testFps(void) {
	eLSA::DISPLAY::Display_SSD1306::fill(eLSA::DISPLAY::White);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";
    char initText[] = "Testing...";

    eLSA::DISPLAY::Display_SSD1306::setCursor(2,0);
    eLSA::DISPLAY::Display_SSD1306::writeString(initText, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);

    do {
    	eLSA::DISPLAY::Display_SSD1306::setCursor(2, 18);
    	eLSA::DISPLAY::Display_SSD1306::writeString(message, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);
    	eLSA::DISPLAY::Display_SSD1306::updateScreen();

        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        fps++;
        end = HAL_GetTick();
    } while((end - start) < 5000);

    char buff[64];
    fps = (float)fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);

    eLSA::DISPLAY::Display_SSD1306::fill(eLSA::DISPLAY::White);
    eLSA::DISPLAY::Display_SSD1306::setCursor(2, 18);
    eLSA::DISPLAY::Display_SSD1306::writeString(buff, eLSA::DISPLAY::Font_11x18, eLSA::DISPLAY::Black);
    eLSA::DISPLAY::Display_SSD1306::updateScreen();
}

/* private methods*/
unsigned int eLSA::DISPLAY::Display_SSD1306::_write_i2c_command(uint8_t command)
{
	return _i2c_interface->writeCommand(DISPLAY_SSD1306_I2C_COMMAND_REGISTER,1,&command,1,DISPLAY_SSD1306_I2C_TIMEOUT);
}

unsigned int eLSA::DISPLAY::Display_SSD1306::_write_i2c_data(uint8_t* p_data, uint16_t data_size)
{
	return _i2c_interface->writeData(DISPLAY_SSD1306_I2C_DATA_REGISTER, 1, p_data, data_size, DISPLAY_SSD1306_I2C_TIMEOUT);
}


