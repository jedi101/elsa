/*
 * PWMDriver.h
 *
 *  Created on: 27.12.2018
 *      Author: Tobias
 */

#ifndef DEVICES_ACTUATORS_PWMDRIVERPC9685_H_
#define DEVICES_ACTUATORS_PWMDRIVERPC9685_H_

#include <cstdint>
#include <comDevices/StmI2cDevice.h>

// I2C constants
#define PWM_DRIVER_PC9685_I2C_DEFAULT_ADDR 		0x60	///< The standard i2c address used for the pwm motorcontroller
#define PWM_DRIVER_PC9685_I2C_TIMEOUT			100		///< The Standard timeout for the I2C interface
#define PWM_DRIVER_PC9685_I2C_ADDRESS_LENGTH	1		/**< The length of the register addresses of the PC9685 pwm controller in byte
														* The PC9685 uses 7Bit addressing -> 1 Byte
														*/
#define MC_I2C_COMMAND_LENGTH					1		///< The length of the commands used by the PC9685 pwm controller in byte

// PC9685 constants
#define PWM_DRIVER_PC9685_MODE1					0x00	///< mode register for standard modes of the PC9685
#define PWM_DRIVER_PC9685_PRESCALE				0xFE	///< prescaler register
#define PWM_DRIVER_PC9685_BASE_REGISTER			0x06	///< register address of pwm driver 0 -> next driver 4 bytes further
#define PWM_DRIVER_PC9685_PIN_MAX_VALUE			4096	///< maximum value for pwm on or off cycle
#define PWM_DRIVER_PC9685_MAX_FREQUENCY			 200	///< maximum pwm frequency for the PCA9685

namespace eLSA {
//! wrapping all actuators used for eLSA
namespace actuators {

/**
 * @author Tobias Koppmann
 * @date 27.12.2018
 *
 * @brief This class impersonates a PC9685 PWM Driver Controller
 *  It encapsulates the usage of the I2C interface which is used to communicate with the PC9685 controller.
 */
class PWMDriverPC9685 {
	public:
		/**
		 * @param i2c_port A STM32 HAL handle describing the used I2C interface
		 * @param deviceAddress The I2C address of the pwm controller
		 *
		 * @throws Exception Thrown if problems with the internal creation of the I2C interface object occur
		 */
		PWMDriverPC9685(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);

		/**
		 * @brief The Destructor deletes the internally used STM_I2C_Device
		 */
		virtual ~PWMDriverPC9685();

		/**
		 * @brief This method resets the pwm controller to initial state
		 *
		 * @throws Exception Thrown if any Exception during the usage of the I2C interface occur
		 */
		void reset(void);

		/**
		 * @brief This method sets the frequency of the internal oscillator
		 * @param freq the desired frequency the oscillator shall be set to
		 *
		 * @throws Exception Thrown if any Exception during the usage of the I2C interface occur
		 */
		void setPWMFreq(float freq);

		/**
		 * @brief This method sets the duty cycle states for a certain pin on the pwm controller
		 * @param num The numerical identifier of the output pin that is set
		 * @param on The high level portion of a pwm duty cycle of the pin
		 * @param on The low level portion of a pwm duty cycle of the pin
		 *
		 * @throws Exception Thrown if any Exception during the usage of the I2C interface occur
		 */
		void setPWM(uint8_t num, uint16_t on, uint16_t off);

	private:

		eLSA::comDevices::StmI2cDevice* _i2cInterface;
		I2C_HandleTypeDef* _i2cPort;
		uint16_t _i2cAddress = PWM_DRIVER_PC9685_I2C_DEFAULT_ADDR;
};

} /* namespace actuators */
} /* namespace eLSA */

#endif /* DEVICES_ACTUATORS_PWMDRIVERPC9685_H_ */
