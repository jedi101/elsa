/*
 * I2CDevice.cpp
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#include <comDevices/STM_I2C_Device.h>
#include <cstdint>

namespace eLSA {

	//constructor for I2C device
	STM_I2C_Device::STM_I2C_Device(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress)
		:_i2cPort{i2cPort}, _deviceAddress{deviceAddress}{}

	//destructor for I2C device
	STM_I2C_Device::~STM_I2C_Device(){};

	//set register address used for writing or reading
	int STM_I2C_Device::setDeviceRegisterParams(uint16_t pRegisterAddress, uint16_t sizeRegisterAddress){
		int returnValue = -1;

		if(pRegisterAddress && sizeRegisterAddress) {
			this->_pRegisterAddress = pRegisterAddress;
			this->_sizeRegisterAddress = sizeRegisterAddress;
			returnValue = 0;
		}

		return returnValue;
	}

	//set connection timeout
	void STM_I2C_Device::setConnectionTimeout(uint32_t time){
		if(time) {
			this->_timeout = time;
		}
	}

	// write data to I2C device
	int STM_I2C_Device::writeData(uint8_t* pData, uint16_t sizeData)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2cPort, _deviceAddress,5,_timeout);
		} while(_status == HAL_BUSY);

		//only try to send data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Write(_i2cPort, _deviceAddress, _pRegisterAddress, _sizeRegisterAddress, pData, sizeData, _timeout);
			} while(_status == HAL_BUSY);
		}

		return (int)_status;
	}

	// read data from I2C device
	int STM_I2C_Device::readData(uint8_t* pData, uint16_t sizeData)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2cPort, _deviceAddress,5,_timeout);
		} while(_status == HAL_BUSY);

		//only try to read data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Read(_i2cPort, _deviceAddress, _pRegisterAddress, _sizeRegisterAddress, pData, sizeData, _timeout);
			} while(_status == HAL_BUSY);
		}

		return (int)_status;
	}


} /* namespace eLSA */
