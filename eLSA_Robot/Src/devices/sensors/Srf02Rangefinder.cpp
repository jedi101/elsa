/*
 * SRF02Rangefinder.cpp
 *
 *  Created on: 10.12.2018
 *      Author: Tobias
 */

#include <comDevices/StmI2cDevice.h>
#include <sensors/Srf02Rangefinder.h>
#include "comDevices/IComDriver.h"

namespace eLSA {
namespace sensors {

Srf02RangefinderI2c::Srf02RangefinderI2c(eLSA::hwInterfaces::StmI2cDevice* hwInterface)
	: _i2cInterface{hwInterface}
{
	//check which kind of hardware interface is used and if pointer exists at all
	if(hwInterface) {
		_i2cInterface->setConnectionTimeout(eLSA::sensors::I2C_DEFAULT_TIMEOUT);

	}
}

int Srf02RangefinderI2c::getDistance(const uint8_t* queryType)
{
	unsigned short sensorData = 0;

	//catch missing required parameters
	if((!queryType) || (!_i2cInterface)){
		return -1;
	}

	// if object uses i2c interface
	if(_i2cInterface) {
		_i2cInterface->setDeviceRegisterParams(_i2cCmdRegister, 1);
		_i2cInterface->writeData((uint8_t*)queryType, 1);
		HAL_Delay(_delayMeasurementMilliseconds);
		_i2cInterface->setDeviceRegisterParams(_i2cRangeHighByte, 1);
		_i2cInterface->readData((uint8_t*)&sensorData, 1);
		sensorData = sensorData << 8;
		_i2cInterface->setDeviceRegisterParams(_i2cRangeLowByte, 1);
		_i2cInterface->readData((uint8_t*)&sensorData, 1);
	}

	return (int)sensorData;
}

int Srf02RangefinderI2c::getDistanceInches()
{
	return Srf02RangefinderI2c::getDistance(&_cmdQueryMeasurementInches);
}

int Srf02RangefinderI2c::getDistanceCentimeters()
{
	return Srf02RangefinderI2c::getDistance(&_cmdQueryMeasurementCentimeters);
}

int Srf02RangefinderI2c::getDistanceMicroseconds()
{
	return Srf02RangefinderI2c::getDistance(&_cmdQueryMeasurementMicroseconds);
}

int Srf02RangefinderI2c::forceAutotune()
{
	return 0;
}

int Srf02RangefinderI2c::emitBurst40kHz()
{
	return 0;
}

int Srf02RangefinderI2c::setHwInterface(eLSA::hwInterfaces::StmI2cDevice* hwInterface)
{
	return 0;
}

int Srf02RangefinderI2c::isDistanceLowerCentimeters(int threshold)
{
	return 0;
}

int Srf02RangefinderI2c::isDistanceLowerInches(int threshold)
{
	return 0;
}

int Srf02RangefinderI2c::isDistanceLowerMicroseconds(int threshold)
{
	return 0;
}

} /* namespace sensors */
} /* namespace eLSA */
