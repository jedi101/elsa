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
	 */
	static Motorcontroller* instance();

	/**
	 * @brief This method runs a certain motor.
	 * The desired speed has to be set beforehand by using setMotorSpeed()
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 */
	void runMotor(uint8_t motor, MotorDirection dir);

	/**
	 * @brief This method sets the desired speed for a certain motor
	 *
	 * @param motor The index of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 */
	void setMotorSpeed(uint8_t motor, uint8_t speed);

	/**
	 * @brief This method runs a certain motor with a given speed
	 *
	 * @param motor The index of the motor
	 * @param dir The desired rotation direction of the motor
	 * @param speed The desired speed for that motor in a range of 0 to 255
	 */
	void runMotorWithSpeed(uint8_t motor, MotorDirection dir, uint8_t speed);

private:
	static constexpr Motorcontroller* _instance = 0;
	Motorcontroller();
	Motorcontroller(const Motorcontroller&);
	~Motorcontroller();

	eLSA::hwInterfaces::StmI2cDevice* _i2cInterface;
	struct MotorDC _motor[4];

};

} /* namespace actuators */
} /* namespace eLSA */

#endif /* DEVICES_ACTUATORS_MOTORCONTROLLER_H_ */
