/*
 * Motorcontroller.cpp
 *
 *  Created on: 23.11.2018
 *      Author: Tobias
 */

#include "actuators/Motorcontroller.h"

namespace eLSA {
namespace actuators {

// initialize singleton instance
Motorcontroller* Motorcontroller::_instance = 0;

//Constructor which is called in instance()
Motorcontroller::Motorcontroller(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress)
	: _i2cPort{i2cPort}, _i2cAddress{deviceAddress}
{
	if(_i2cPort && _i2cAddress) {

		//retrieve new i2c interface object
		_i2cInterface = new eLSA::comDevices::StmI2cDevice(_i2cPort, _i2cAddress);

		if(_i2cInterface) {

			//set display standard timeout for i2c device
			_i2cInterface->setConnectionTimeout(MC_I2C_TIMEOUT);

		}
	}

}

Motorcontroller::~Motorcontroller() {

}

Motorcontroller* Motorcontroller::instance(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress) {
	if (!_instance) {
		_instance = new Motorcontroller(i2cPort, deviceAddress);
	}

	return _instance;
}

unsigned int Motorcontroller::runMotor(uint8_t motorIdx, MotorDirection dir) {
	unsigned int _status = HAL_ERROR;
	uint8_t _buffer[10] = {0}; // 10 Byte for 2 Pins which use 5 Bytes each

	if(motorIdx < MC_MOTOR_COUNT) {

		_buffer[0] = MC_I2C_PWM_DRIVER_BASE_REGISTER + (4*_motor[motorIdx].directionalPin1); //write to 1st directional pin
		_buffer[5] = MC_I2C_PWM_DRIVER_BASE_REGISTER + (4*_motor[motorIdx].directionalPin2); //write to 2nd directional pin

		switch(dir) {
			case STOP:
				//nothing to do here since only 0 values are necessary to stop
			  break;

			case FORWARD:
				_buffer[1] = MC_I2C_PWM_PIN_MAX_VALUE & 0xFF; //get low byte
				_buffer[2] = (MC_I2C_PWM_PIN_MAX_VALUE >> 8) & 0xFF; //get high byte
				//buffer[3..4] and [6..9] have to stay 0
			  break;

			case BACKWARDS:
				//buffer[1..5] have to stay 0
				_buffer[6] = MC_I2C_PWM_PIN_MAX_VALUE & 0xFF; //get low byte
				_buffer[7] = (MC_I2C_PWM_PIN_MAX_VALUE >> 8) & 0xFF; //get high byte
				//buffer[8..9] have to stay 0
			  break;

			default:
			  break;
		}

		_i2cInterface->setDeviceRegisterParams(MC_I2C_PC9685_MODE1, MC_I2C_ADDRESS_LENGTH);
		_status = _i2cInterface->writeData(_buffer, sizeof(_buffer));

	}

	return (unsigned int)_status;
}

unsigned int Motorcontroller::setMotorSpeed(uint8_t motorIdx, uint8_t speed) {
	unsigned int _status = HAL_ERROR;
	uint8_t _buffer[3] = {0}; // 1 address byte, 2 value bytes

	uint16_t _calculatedSpeed = speed * 16;

	if(motorIdx < MC_MOTOR_COUNT) {

		_buffer[0] = MC_I2C_PWM_DRIVER_BASE_REGISTER + (4*_motor[motorIdx].pwmPin);

		//check if "all on" is more sensible
		 if (speed > 4095) {
			 _buffer[1] = MC_I2C_PWM_PIN_MAX_VALUE & 0xFF; //get low byte
			 _buffer[2] = (MC_I2C_PWM_PIN_MAX_VALUE >> 8) & 0xFF; //get high byte
		 } else {
			 _buffer[1] = _calculatedSpeed & 0xFF; //get low byte
			 _buffer[2] = (_calculatedSpeed>>8) & 0xFF; // get high byte
		 }

		_i2cInterface->setDeviceRegisterParams(MC_I2C_PC9685_MODE1, MC_I2C_ADDRESS_LENGTH);
		_status = _i2cInterface->writeData(_buffer, sizeof(_buffer));

	}

	return (unsigned int)_status;

}

unsigned int Motorcontroller::runMotorWithSpeed(uint8_t motorIdx, MotorDirection dir, uint8_t speed) {
	unsigned int _status = HAL_ERROR;

	_status = Motorcontroller::setMotorSpeed(motorIdx, speed);

	if(_status != HAL_ERROR)
		_status = Motorcontroller::runMotor(motorIdx, dir);

	return _status;
}

unsigned int Motorcontroller::reset() {
	uint8_t command = 0x00; //value to reset PCA9685

	_i2cInterface->setDeviceRegisterParams(MC_I2C_PC9685_MODE1, MC_I2C_ADDRESS_LENGTH);
	return _i2cInterface->writeData(&command, MC_I2C_COMMAND_LENGTH);
}

} /* namespace actuators */
} /* namespace eLSA */
