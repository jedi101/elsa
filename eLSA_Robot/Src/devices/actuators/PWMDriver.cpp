/*
 * PWMDriver.cpp
 *
 *  Created on: 08.01.2019
 *      Author: Tobias
 */

#include <actuators/PWMDriver.h>
#include <cstdint>
#include <comDevices/StmI2cDevice.h>
#include <cmath>
#include <exception>

namespace eLSA {
namespace actuators {

PWMDriverPC9685::PWMDriverPC9685(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress)
	:_i2cPort{i2cPort}, _i2cAddress{deviceAddress}
{

	if(_i2cPort && _i2cAddress) {
		//retrieve new i2c interface object
		_i2cInterface = new eLSA::comDevices::StmI2cDevice(_i2cPort, _i2cAddress);

		if(_i2cInterface) {
			//set display standard timeout for i2c device
			_i2cInterface->setConnectionTimeout(PWM_DRIVER_PC9685_I2C_TIMEOUT);
		} else {
			throw "was not able to create i2c interface object";
		}
	}
}

PWMDriverPC9685::~PWMDriverPC9685() {
	delete _i2cInterface;
}

void PWMDriverPC9685::reset() {
	uint8_t _buffer = 0x00;

	try {
		_i2cInterface->setDeviceRegisterParams(PWM_DRIVER_PC9685_MODE1, 1);
	} catch(...) {
		throw;
	}

	try {
		_i2cInterface->writeData(&_buffer,sizeof(_buffer));
	} catch(...) {
		throw;
	}

}

void PWMDriverPC9685::setPWMFreq(float freq) {
	float prescaleval;
	uint8_t oldmode, newmode, prescale;

	freq *= 0.9;  // Correct for overshoot in the frequency setting

	prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale = floor(prescaleval);

	//### set writing target register to mode register
	try {
		_i2cInterface->setDeviceRegisterParams(PWM_DRIVER_PC9685_MODE1, 1);
	} catch(...) {
		throw;
	}

	//### get old mode
	try {
		_i2cInterface->readData(&oldmode, 1);
	} catch(...) {
		throw;
	}

	//### set sleep mode (Bit 4 in Mode 1 Register)
	newmode = (oldmode & 0x7F) | 0x10; // 0x7F mask to clear restart bit
	try {
		_i2cInterface->writeData(&newmode, 1); // go to sleep
	} catch(...) {
		throw;
	}

	//### set prescaler
	//set writing target register to prescaler register
	try {
		_i2cInterface->setDeviceRegisterParams(PWM_DRIVER_PC9685_PRESCALE, 1);
	} catch(...) {
		throw;
	}

	try {
		 _i2cInterface->writeData(&prescale, 1);
	} catch(...) {
		throw;
	}

	//reset old mode
	try {
		 _i2cInterface->setDeviceRegisterParams(PWM_DRIVER_PC9685_MODE1, 1);
	} catch(...) {
		throw;
	}

	try {
		 _i2cInterface->writeData(&oldmode, 1);
	} catch(...) {
		throw;
	}

	//wait and activate auto increment
	HAL_Delay(10);
	oldmode |= 0xA1;
	try {
		 _i2cInterface->writeData(&oldmode, 1);  //  This sets the MODE1 register to turn on auto increment.
	} catch(...) {
		throw;
	}
}

void PWMDriverPC9685::setPWM(uint8_t pin, uint16_t on, uint16_t off) {
	uint8_t _buffer[5] = {0}; // 1 address byte, 2 value bytes

	_buffer[0] = PWM_DRIVER_PC9685_BASE_REGISTER + (4*pin);
	_buffer[1] = on & 0xFF; //get low byte
	_buffer[2] = (on>>8) & 0xFF; // get high byte
	_buffer[3] = off & 0xFF; //get low byte
	_buffer[4] = (off>>8) & 0xFF; // get high byte

	try {
		_i2cInterface->setDeviceRegisterParams(PWM_DRIVER_PC9685_MODE1, PWM_DRIVER_PC9685_I2C_ADDRESS_LENGTH);
	} catch(...) {
		throw;
	}

	try {
		_i2cInterface->writeData(_buffer, sizeof(_buffer));
	} catch(...) {
		throw;
	}

}

} /* namespace actuators */
} /* namespace eLSA */
