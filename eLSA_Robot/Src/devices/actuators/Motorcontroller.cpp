/*
 * Motorcontroller.cpp
 *
 *  Created on: 23.11.2018
 *      Author: Tobias
 */

#include <actuators/Motorcontroller.h>

namespace eLSA {
namespace actuators {

Motorcontroller::Motorcontroller(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress) {
	if(i2cPort && deviceAddress) {
		_pwm = new PWMDriverPC9685(i2cPort, deviceAddress);

		_pwm->reset();
		_pwm->setPWMFreq(PWM_DRIVER_PC9685_MAX_FREQUENCY);

		for (uint8_t i=0; i<16; i++)
		    _pwm->setPWM(i, 0, 0);
	} else {
		throw "invalid parameter";
	}

	_motor[0].directionalPin1 = 10;
	_motor[0].directionalPin2 = 9;
	_motor[0].pwmPin = 8;

	_motor[1].directionalPin1 = 11;
	_motor[1].directionalPin2 = 12;
	_motor[1].pwmPin = 13;

}

Motorcontroller::~Motorcontroller() {

}

void Motorcontroller::runMotor(uint8_t motorIdx, MotorDirection_t dir) {

	if(motorIdx < MC_MOTOR_COUNT) {

		switch(dir) {
			case STOP:
				try {
					setPin(_motor[motorIdx].directionalPin1, 0);
					setPin(_motor[motorIdx].directionalPin2, 0);
				} catch(...) {
					throw;
				}
				break;

			case FORWARD:
				try {
					setPin(_motor[motorIdx].directionalPin1, 1);
					setPin(_motor[motorIdx].directionalPin2, 0);
				} catch(...) {
					throw;
				}
			    break;

			case BACKWARDS:
				try {
					setPin(_motor[motorIdx].directionalPin2, 1);
					setPin(_motor[motorIdx].directionalPin1, 0);
				} catch(...) {
					throw;
				}
			    break;

			default:
			  break;
		}

	} else {
		throw "invalid parameter => motorIdx too big";
	}

}

void Motorcontroller::setMotorSpeed(uint8_t motorIdx, uint8_t speed) {

	if(motorIdx < MC_MOTOR_COUNT) {
		//check if "all on" is more sensible
		setPWM(_motor[motorIdx].pwmPin, speed*16);
	} else {
		throw "invalid parameter => motorIdx too big";
	}

}

void Motorcontroller::runMotorWithSpeed(uint8_t motorIdx, MotorDirection_t dir, uint8_t speed) {

	//set motor speed
	try {
		setMotorSpeed(motorIdx, speed);
	} catch(...) {
		throw;
	}

	//run motor
	try {
		runMotor(motorIdx, dir);
	} catch(...) {
		throw;
	}

}

void Motorcontroller::setPin(uint8_t pin, uint16_t value) {
	try {
		if (value == 0)
			_pwm->setPWM(pin, 0, 0);
		else
			_pwm->setPWM(pin, 4096, 0);
	} catch(...) {
		throw;
	}
}

void Motorcontroller::setPWM(uint8_t pin, uint16_t value) {
	try {
		if (value > 4095) {
			_pwm->setPWM(pin, 4096, 0);
		} else
			_pwm->setPWM(pin, 0, value);
	} catch(...) {
		throw;
	}
}

} /* namespace actuators */
} /* namespace eLSA */
