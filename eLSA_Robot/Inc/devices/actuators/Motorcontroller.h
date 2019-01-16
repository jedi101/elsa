/*
 * Motorcontroller.h
 *
 *  Created on: 23.11.2018
 *      Author: Tobias
 */

#ifndef DEVICES_ACTUATORS_MOTORCONTROLLER_H_
#define DEVICES_ACTUATORS_MOTORCONTROLLER_H_

#include <actuators/PWMDriverPC9685.h>
#include <cstdint>

//general constants
#define MC_MOTOR_COUNT						4		///< count of controllable motors

namespace eLSA {
namespace actuators {

/// This struct holds the pin configuration of the pwm controller for a single motor
struct MotorDC_t{
	uint8_t pwmPin; ///< This value describes the outpin on the pwm controller which is connected to the pwm input on the motor driver chip
	uint8_t directionalPin1; ///< This value describes the outpin on the pwm controller which is connected to the directional port A on the motor driver chip
	uint8_t directionalPin2; ///< This value describes the outpin on the pwm controller which is connected to the directional port B on the motor driver chip
};

/// This enum describes the three possible motor states
typedef enum {
	STOP, ///< The motor is stopped
	FORWARD, ///< The motor is running forward
	BACKWARDS ///< The motor is running backwards
} MotorDirection_t;

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
	Motorcontroller(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);
	~Motorcontroller();

	/**
	 * @brief This method runs a certain motor.
	 * The desired speed has to be set beforehand by using setMotorSpeed()
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 *
	 * @throws Exception Is thrown if invalid motor index is passed as parameter
	 */
	void runMotor(uint8_t motorIdx, MotorDirection_t dir);

	/**
	 * @brief This method sets the desired speed for a certain motor
	 *
	 * @param motor The index of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 *
	 * @throws Exception Is thrown if invalid motor index is passed as parameter or passes an exception thrown by the pwm controller functions
	 */
	void setMotorSpeed(uint8_t motorIdx, uint8_t speed);

	/**
	 * @brief This method runs a certain motor with a given speed
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 *
	 * @throws Exception Passes an exception thrown by functions setMotorSpeed or runMotor
	 */
	void runMotorWithSpeed(uint8_t motorIdx, MotorDirection_t dir, uint8_t speed);

private:
	PWMDriverPC9685* _pwm;
	struct MotorDC_t _motor[MC_MOTOR_COUNT];

    void setPWM(uint8_t pin, uint16_t val);
    void setPin(uint8_t pin, uint16_t val);
};

} /* namespace actuators */
} /* namespace eLSA */

#endif /* DEVICES_ACTUATORS_MOTORCONTROLLER_H_ */
