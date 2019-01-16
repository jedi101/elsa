

#ifndef DISPLAY_SSD1306_H_
#define DISPLAY_SSD1306_H_

#include <comDevices/StmI2cDevice.h>
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
#define DISPLAY_SSD1306_I2C_ADDRESS_LENGTH		1 /**< The length of the register addresses of the ssd1306 controller in byte.
													* The ssd1306 uses 7Bit addressing -> 1 Byte
													*/
#define DISPLAY_SSD1306_I2C_COMMAND_LENGTH		1 /**< The length of the commands used by the ssd1306
													*/

namespace eLSA {
namespace display {

/**
 * @variable static const FontDef_t Font_7x10
 * @brief This struct variable can be used as a 7x10 pixel font for the display methods
 */
static const FontDef_t Font_7x10  = {7, 10, Font7x10};

/**
 * @variable static const FontDef_t Font_11x18
 * @brief This struct variable can be used as a 11x18 pixel font for the display methods
 */
static const FontDef_t Font_11x18 = {11, 18, Font11x18};

/**
 * @variable static const FontDef_t Font_16x26
 * @brief This struct variable can be used as a 16x26 pixel font for the display methods
 */
static const FontDef_t Font_16x26 = {16, 26, Font16x26};

/**
 * @author Tobias Koppmann
 * @date 17.11.2018
 * This struct provides both color values for black and white display
 */
typedef enum {
    Black = 0x00, ///< Black color, no pixel
    White = 0x01  ///< Pixel is set. Color depends on OLED
} Color_t;


/**
 * @author Tobias Koppmann
 * @date 17.11.2018
 * This struct stores information of the display state
 */
typedef struct {
    uint16_t CurrentX; ///< The current x position of the cursor on the screen
    uint16_t CurrentY; ///< The current y position of the cursor on the screen
    uint8_t Inverted; ///< Flag which sets color inversion
    uint8_t Initialized; ///< Flag which tells if the display is already initialized
} Display_t;

/**
 * @author Tobias Koppmann
 * @date 17.11.2018
 *
 * @brief This class impersonates the used OLED display.
 *  It encapsulates the usage of the I2C interface which is used to communicate with the SSD1306 controller.
 *  Additionally the class provides convenient methods to draw single pixels, characters and even strings on the screen.
 *  DISCLAIMER: The used methods are heavily based on the stm32-ssd1306 C library by Aleksander Alekseev (https://github.com/afiskon/stm32-ssd1306)
 */
class DisplaySSD1306 {
public:
	/**
	 * @param i2c_port A STM32 HAL handle describing the used I2C interface
	 * @param i2c_address The I2C address of the display controller
	 */
	DisplaySSD1306(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);

	/**
	 * @brief The Destructor deletes the internally used STM_I2C_Device
	 */
	virtual ~DisplaySSD1306();

	/**
	 * @brief This method fills the whole display with one given color
	 * @param color The color with which the display shall be filled
	 */
	void fill(Color_t color);

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
	void drawPixel(uint8_t x, uint8_t y, Color_t color);

	/**
	 * @brief This method draws a character based on the fonts given in DisplayFonts.h
	 * @param ch The character which is written to the display
	 * @param font The font that is used
	 * @param color The color which the drawn pixel shall have
	 * @return The before written character for validation
	 */
	char writeChar(char ch, FontDef_t font, Color_t color);

	/**
	 * @brief This method draws a character based on the fonts given in DisplayFonts.h
	 * @param str The character array which is written to the display
	 * @param font The font that is used
	 * @param color The color which the drawn pixel shall have
	 * @return The first character of the before written string for validation
	 */
	char writeString(char* str, FontDef_t font, Color_t color);

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
	void _writeI2cCommand(uint8_t command);
	void _writeI2cData(uint8_t* data, uint16_t data_size);

	eLSA::comDevices::StmI2cDevice* _i2cInterface;
	I2C_HandleTypeDef* _i2cPort;
	uint16_t _i2cAddress = DISPLAY_SSD1306_I2C_DEFAULT_ADDR;
	uint8_t _screenBuffer[(DISPLAY_SSD1306_WIDTH * DISPLAY_SSD1306_HEIGHT)/8];
	eLSA::display::Display_t _screenObject;
	uint8_t ssd1306InitCommands[28] = {
		0xAE, //display off
		0x20, //Set Memory Addressing Mode
		0x10, // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode;
								  // 10,Page Addressing Mode (RESET); 11,Invalid
		0xB0, //Set Page Start Address for Page Addressing Mode,0-7
		0xC8, //Set COM Output Scan Direction
		0x00, //---set low column address
		0x10, //---set high column address
		0x40, //--set start line address - CHECK
		0x81, //--set contrast control register - CHECK
		0xFF,
		0xA1, //--set segment re-map 0 to 127 - CHECK
		0xA6, //--set normal color
		0xA8, //--set multiplex ratio(1 to 64) - CHECK
		0x3F,
		0xA4, //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
		0xD3, //-set display offset - CHECK
		0x00, //-not offset
		0xD5, //--set display clock divide ratio/oscillator frequency
		0xF0, //--set divide ratio
		0xD9, //--set pre-charge period
		0x22,
		0xDA, //--set com pins hardware configuration - CHECK
		0x12,
		0xDB, //--set vcomh
		0x20, //0x20,0.77xVcc
		0x8D, //--set DC-DC enable
		0x14,
		0xAF //--turn on SSD1306 panel
	};
};

} /* namespace DISPLAY*/
} /* namespace eLSA */

#endif /* DISPLAY_SSD1306_H_ */
