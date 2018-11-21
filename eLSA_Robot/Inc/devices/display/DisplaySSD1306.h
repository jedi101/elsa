/*
 * DisplaySSD1306.h
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#ifndef DISPLAY_SSD1306_H_
#define DISPLAY_SSD1306_H_

#include <comDevices/STM_I2C_Device.h>
#include "display/DisplayFonts.h"

#define DISPLAY_SSD1306_I2C_DEFAULT_ADDR        (0x3C << 1)
#define DISPLAY_SSD1306_I2C_COMMAND_REGISTER	0x00
#define DISPLAY_SSD1306_I2C_TIMEOUT				100
#define DISPLAY_SSD1306_I2C_DATA_REGISTER		0x40
#define DISPLAY_SSD1306_WIDTH					128
#define DISPLAY_SSD1306_HEIGHT					64

namespace eLSA {

namespace DISPLAY {
static const FontDef Font_7x10  = {7, 10, Font7x10};
static const FontDef Font_11x18 = {11, 18, Font11x18};
static const FontDef Font_16x26 = {16, 26, Font16x26};

typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} DISPLAY_SSD1306_COLOR;


// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} DISPLAY_SSD1306_t;

/**
 *
 */
class Display_SSD1306 {
public:
	Display_SSD1306(I2C_HandleTypeDef* i2c_port, uint16_t i2c_address);
	Display_SSD1306(I2C_HandleTypeDef* i2c_port, uint16_t device_address, unsigned int width, unsigned height);
	virtual ~Display_SSD1306();
	void fill(DISPLAY_SSD1306_COLOR color);
	void updateScreen(void);
	void drawPixel(uint8_t x, uint8_t y, DISPLAY_SSD1306_COLOR color);
	char writeChar(char ch, FontDef font, DISPLAY_SSD1306_COLOR color);
	char writeString(char* str, FontDef font, DISPLAY_SSD1306_COLOR color);
	void setCursor(uint8_t x, uint8_t y);
	void testFps(void);

private:
	unsigned int _write_i2c_command(uint8_t command);
	unsigned int _write_i2c_data(uint8_t* data, uint16_t data_size);

	eLSA::STM_I2C_Device* _i2c_interface;
	I2C_HandleTypeDef* _i2c_port;
	uint16_t _i2c_address = DISPLAY_SSD1306_I2C_DEFAULT_ADDR;
	uint8_t screenBuffer[(DISPLAY_SSD1306_WIDTH * DISPLAY_SSD1306_HEIGHT)/8];
	eLSA::DISPLAY::DISPLAY_SSD1306_t screen_object;

};

} /* namespace DISPLAY*/
} /* namespace eLSA */

#endif /* DISPLAY_SSD1306_H_ */
