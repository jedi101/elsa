/*
 * I2CDevice.cpp
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#include <comDevices/StmI2cDevice.h>
#include <cstdint>

namespace eLSA {
namespace comDevices {

	//constructor for I2C device
	StmI2cDevice::StmI2cDevice(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress)
		:_i2cPort{i2cPort}, _deviceAddress{deviceAddress}{}

	//destructor for I2C device
	StmI2cDevice::~StmI2cDevice(){}

	//set register address used for writing or reading
	void StmI2cDevice::setDeviceRegisterParams(uint16_t registerAddress, uint16_t sizeRegisterAddress){

		if(sizeRegisterAddress) {
			this->_registerAddress = registerAddress;
			this->_sizeRegisterAddress = sizeRegisterAddress;
		} else {
			throw "invalid parameter";
		}
	}

	//set connection timeout
	void StmI2cDevice::setConnectionTimeout(uint32_t time){
		if(time) {
			this->_timeout = time;
		} else {
			throw "invalid parameter";
		}
	}

	// write data to I2C device
	void StmI2cDevice::writeData(uint8_t* pData, uint16_t sizeData)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2cPort, _deviceAddress,5,_timeout);
		} while(_status == HAL_BUSY);

		//only try to send data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Write(_i2cPort, _deviceAddress, _registerAddress, _sizeRegisterAddress, pData, sizeData, _timeout);
			} while(_status == HAL_BUSY);

			if(_status != HAL_OK) {
				throw "I2C writing failed";
			}
		} else {
			throw "I2C device is not ready";
		}

	}

	// read data from I2C device
	void StmI2cDevice::readData(uint8_t* pData, uint16_t sizeData)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2cPort, _deviceAddress,5,_timeout);
		} while(_status == HAL_BUSY);

		//only try to read data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Read(_i2cPort, _deviceAddress, _registerAddress, _sizeRegisterAddress, pData, sizeData, _timeout);
			} while(_status == HAL_BUSY);

			if(_status != HAL_OK) {
				throw "I2C writing failed";
			}
		} else {
			throw "I2C device is not ready";
		}
	}

} /* namespace hw_interfaces*/
} /* namespace eLSA */
