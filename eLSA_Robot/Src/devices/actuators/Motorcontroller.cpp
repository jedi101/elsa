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
} /* namespace actuators */
} /* namespace eLSA */
