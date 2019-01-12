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
	try {
		return getDistance(&_cmdQueryMeasurementInches);
	} catch(...) {
		throw;
	}

}

unsigned int ISrf02Rangefinder::getDistanceInCentimeters(void)
{
	try {
		return getDistance(&_cmdQueryMeasurementCentimeters);
	} catch(...) {
		throw;
	}
}

unsigned int ISrf02Rangefinder::getDistanceInMicroseconds(void)
{
	try {
		return getDistance(&_cmdQueryMeasurementMicroseconds);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInCentimeters(unsigned int threshold)
{
	try {
		return (getDistanceInCentimeters() < threshold);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInInches(unsigned int threshold)
{
	try {
		return (getDistanceInInches() < threshold);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInMicroseconds(unsigned int threshold)
{
	try {
		return (getDistanceInMicroseconds() < threshold);
	} catch(...) {
		throw;
	}
}

Srf02RangefinderI2C::Srf02RangefinderI2C(comDevices::StmI2cDevice* hwInterface)
	: _i2cInterface{hwInterface}
{

};

unsigned int Srf02RangefinderI2C::getDistance(const uint8_t* queryType)
{
	uint16_t sensorData = 0;

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
