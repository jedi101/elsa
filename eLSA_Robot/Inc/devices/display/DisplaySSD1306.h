

#ifndef DISPLAY_SSD1306_H_
#define DISPLAY_SSD1306_H_

#include <comDevices/STM_I2C_Device.h>
#include "display/DisplayFonts.h"

#define DISPLAY_SSD1306_I2C_DEFAULT_ADDR        (0x3C << 1) ///< The standard i2c address used for the display
#define DISPLAY_SSD1306_I2C_COMMAND_REGISTER	0x00 ///< The register to which all commands have to be written
#define DISPLAY_SSD1306_I2C_TIMEOUT				100 ///< Standard timeout for the I2C interface
#define DISPLAY_SSD1306_I2C_DATA_REGISTER		0x40 ///< The start address of the memory where all displayed data is written to
#define DISPLAY_SSD1306_WIDTH					128 ///< The width of the display.
#define DISPLAY_SSD1306_HEIGHT					64 /**< The height of the display.
													* For the Adafruit 128x32 Display the value 64 has to be used since it seems
													* that on this display every second row is used.
													*/

namespace eLSA {

namespace DISPLAY {
static const FontDef Font_7x10  = {7, 10, Font7x10};
static const FontDef Font_11x18 = {11, 18, Font11x18};
static const FontDef Font_16x26 = {16, 26, Font16x26};

typedef enum {
    Black = 0x00, ///< Black color, no pixel
    White = 0x01  ///< Pixel is set. Color depends on OLED
} DISPLAY_SSD1306_COLOR;


// Struct to store transformations
typedef struct {
    uint16_t CurrentX; ///< The current x position of the cursor on the screen
    uint16_t CurrentY; ///< The current y position of the cursor on the screen
    uint8_t Inverted; ///< Flag which sets color inversion
    uint8_t Initialized; ///< Flag which tells if the display is already initialized
} DISPLAY_SSD1306_t;

/**
 * @author Tobias Koppmann
 * @date 11/21/2018
 *
 * @brief This class impersonates the used OLED display.
 *  It encapsulates the usage of the I2C interface which is used to communicate with the SSD1306 controller.
 *  Additionally the class provides convenient methods to draw single pixels, characters and even strings on the screen.
 *  DISCLAIMER: The used methods are heavily based on the stm32-ssd1306 C library by Aleksander Alekseev (https://github.com/afiskon/stm32-ssd1306)
 */
class Display_SSD1306 {
public:
	/**
	 * @param i2c_port A STM32 HAL handle describing the used I2C interface
	 * @param i2c_address The I2C address of the display controller
	 */
	Display_SSD1306(I2C_HandleTypeDef* i2c_port, uint16_t i2c_address);

	/**
	 * The Destructor deletes the internally used STM_I2C_Device
	 */
	virtual ~Display_SSD1306();

	/**
	 * @brief This method fills the whole display with one given color
	 * @param color The color with which the display shall be filled
	 */
	void fill(DISPLAY_SSD1306_COLOR color);

	/**
	 * @brief This method has to be called after every command and drawing to show the new display content
	 */
	void updateScreen(void);

	/**
	 * @brief This method draws one single pixel to the display
	 * @param x The x coordinate of the pixel (dimension specified by display width)
	 * @param y The y coordinate of the pixel (dimension specified by display height)
	 * @param color The color which the drawn pixel shall have
	 */
	void drawPixel(uint8_t x, uint8_t y, DISPLAY_SSD1306_COLOR color);

	/**
	 * @brief This method draws a character based on the fonts given in DisplayFonts.h
	 * @param ch The character which is written to the display
	 * @param font The font that is used
	 * @param color The color which the drawn pixel shall have
	 * @return The before written character for validation
	 */
	char writeChar(char ch, FontDef font, DISPLAY_SSD1306_COLOR color);

	/**
	 * @brief This method draws a character based on the fonts given in DisplayFonts.h
	 * @param str The character array which is written to the display
	 * @param font The font that is used
	 * @param color The color which the drawn pixel shall have
	 * @return The first character of the before written string for validation
	 */
	char writeString(char* str, FontDef font, DISPLAY_SSD1306_COLOR color);

	/**
	 * @brief This method sets an offset to the starting point from which is drawn on the display
	 * @param x The x coordinate of the starting pixel (dimension specified by display width)
	 * @param y The y coordinate of the starting pixel (dimension specified by display height)
	 */
	void setCursor(uint8_t x, uint8_t y);

	/**
	 * @brief This method tests the maximum display refresh rate per second and displays the value on the screen
	 */
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
