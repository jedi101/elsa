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

unsigned int ISrf02Rangefinder::getDistanceInInches(void)
{

	return getDistance(&_cmdQueryMeasurementInches);
}

unsigned int ISrf02Rangefinder::getDistanceInCentimeters(void)
{
	return getDistance(&_cmdQueryMeasurementCentimeters);
}

unsigned int ISrf02Rangefinder::getDistanceInMicroseconds(void)
{
	return getDistance(&_cmdQueryMeasurementMicroseconds);
}

uint8_t ISrf02Rangefinder::isDistanceLowerInCentimeters(int threshold)
{
	return 0;
}

uint8_t ISrf02Rangefinder::isDistanceLowerInInches(int threshold)
{
	return 0;
}

uint8_t ISrf02Rangefinder::isDistanceLowerInMicroseconds(int threshold)
{
	return 0;
}

void ISrf02Rangefinder::forceAutotune(void)
{

}

void ISrf02Rangefinder::emitBurst(void)
{

}

unsigned int Srf02RangefinderI2C::getDistance(const uint8_t* queryType)
{
	unsigned short sensorData = 0;

	// if object uses i2c interface
	try {
		_i2cInterface->setDeviceRegisterParams(_i2cCmdRegister, 1);
		_i2cInterface->writeData((uint8_t*)queryType, 1);
		HAL_Delay(_delayMeasurementMilliseconds);
		_i2cInterface->setDeviceRegisterParams(_i2cRangeHighByte, 1);
		_i2cInterface->readData((uint8_t*)&sensorData, 1);
		sensorData = sensorData << 8;
		_i2cInterface->setDeviceRegisterParams(_i2cRangeLowByte, 1);
		_i2cInterface->readData((uint8_t*)&sensorData, 1);
	} catch(...) {
		throw;
	}

	return (unsigned int)sensorData;
}

} /* namespace sensors */
} /* namespace eLSA */
