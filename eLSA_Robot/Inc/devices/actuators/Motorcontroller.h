/*
 * Motorcontroller.h
 *
 *  Created on: 23.11.2018
 *      Author: Tobias
 */

#ifndef DEVICES_ACTUATORS_MOTORCONTROLLER_H_
#define DEVICES_ACTUATORS_MOTORCONTROLLER_H_

#include <cstdint>
#include <comDevices/StmI2cDevice.h>

// I2C constants
#define MC_I2C_DEFAULT_ADDR 				0x40	///< The standard i2c address used for the pwm motorcontroller
#define MC_I2C_TIMEOUT						100		///< The Standard timeout for the I2C interface
#define MC_I2C_ADDRESS_LENGTH				1		/**< The length of the register addresses of the PC9685 pwm controller in byte
													* The PC9685 uses 7Bit addressing -> 1 Byte
													*/
#define MC_I2C_COMMAND_LENGTH				1		///< The length of the commands used by the PC9685 pwm controller in byte

// PC9685 constants
#define MC_I2C_PC9685_MODE1					0x00	///< mode register for standard modes of the PC9685
#define MC_I2C_PCA9685_PRESCALE				0xFE	///< prescaler register
#define MC_I2C_PWM_DRIVER_BASE_REGISTER		0x06	///< register address of pwm driver 0 -> next driver 4 bytes further
#define MC_I2C_PWM_PIN_MAX_VALUE			4096	///< maximum value for pwm on or off cycle

//general constants
#define MC_MOTOR_COUNT						4		///< count of controllable motors

namespace eLSA {
namespace actuators {

/// This struct holds the pin configuration of the pwm controller for a single motor
struct MotorDC {
	uint8_t pwmPin; ///< This value describes the outpin on the pwm controller which is connected to the pwm input on the motor driver chip
	uint8_t directionalPin1; ///< This value describes the outpin on the pwm controller which is connected to the directional port A on the motor driver chip
	uint8_t directionalPin2; ///< This value describes the outpin on the pwm controller which is connected to the directional port B on the motor driver chip
};

/// This enum describes the three possible motor states
enum MotorDirection{
	STOP, ///< The motor is stopped
	FORWARD, ///< The motor is running forward
	BACKWARDS ///< The motor is running backwards
};

/**
 * @author Tobias Koppmann
 * @date 11/23/2018
 *
 * @brief This class provides functionality for the operation of up to 4 DC Motors driven by the PCA9685 PWM-Chip and the TB6612FNG Motor-Bridge
 *  as found on the Adafruit Arduino Motorshield V2.
 *  This class is implemented as a singleton since this class shall solely be used for the chassis motors
 */
class Motorcontroller {
public:
	/**
	 * @brief The method that returns a Motorcontroller instance allocated on the heap
	 *
	 * @param i2c_port A STM32 HAL handle describing the used I2C interface
	 * @param deviceAddress The I2C address of the display controller
	 */
	static Motorcontroller* instance(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);

	/**
	 * @brief This method runs a certain motor.
	 * The desired speed has to be set beforehand by using setMotorSpeed()
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 */
	unsigned int runMotor(uint8_t motorIdx, MotorDirection dir);

	/**
	 * @brief This method sets the desired speed for a certain motor
	 *
	 * @param motor The index of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 */
	unsigned int setMotorSpeed(uint8_t motorIdx, uint8_t speed);

	/**
	 * @brief This method runs a certain motor with a given speed
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 */
	unsigned int runMotorWithSpeed(uint8_t motorIdx, MotorDirection dir, uint8_t speed);

	/**
	 * @brief This method resets the pwm controller
	 *
	 */
	unsigned int reset();

private:
	static Motorcontroller* _instance;
	Motorcontroller(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);
	Motorcontroller(const Motorcontroller&);
	~Motorcontroller();

	eLSA::comDevices::StmI2cDevice* _i2cInterface;
	I2C_HandleTypeDef* _i2cPort;
	uint16_t _i2cAddress = MC_I2C_DEFAULT_ADDR;
	struct MotorDC _motor[MC_MOTOR_COUNT];
};

} /* namespace actuators */
} /* namespace eLSA */

#endif /* DEVICES_ACTUATORS_MOTORCONTROLLER_H_ */
