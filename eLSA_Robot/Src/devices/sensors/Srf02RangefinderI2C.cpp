/*
 * SRF02Rangefinder.cpp
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#include <comDevices/StmI2cDevice.h>
#include <sensors/Srf02RangefinderI2C.h>

namespace eLSA {
namespace sensors {

Srf02RangefinderI2C::Srf02RangefinderI2C(comDevices::StmI2cDevice* hwInterface, uint8_t deviceAddress)
	: _i2cInterface{hwInterface}, _i2cAddress{deviceAddress}
{};

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
