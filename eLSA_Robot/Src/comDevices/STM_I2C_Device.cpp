/*
 * I2CDevice.cpp
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#include <comDevices/STM_I2C_Device.h>
#include <cstdint>

namespace eLSA {

	STM_I2C_Device::STM_I2C_Device(I2C_HandleTypeDef* i2c_port, uint16_t device_address)
		:_i2c_port{i2c_port}, _device_address{device_address}{}

	STM_I2C_Device::~STM_I2C_Device(){};

	unsigned int STM_I2C_Device::writeCommand(uint16_t pAddressCommand, uint16_t sizeAddressCommand, uint8_t* pCommand, uint16_t sizeCommand, uint32_t timeout)
	{
		return STM_I2C_Device::writeData(pAddressCommand, sizeAddressCommand, pCommand, sizeCommand, timeout);
	}

	unsigned int STM_I2C_Device::writeData(uint16_t pAddressDataRegister, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2c_port, _device_address,5,timeout);
		} while(_status == HAL_BUSY);

		//only try to send data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Write(_i2c_port, _device_address, pAddressDataRegister, sizeAddressData, pData, sizeData, timeout);
			} while(_status == HAL_BUSY);
		}

		return _status;
	}

	unsigned int STM_I2C_Device::readData(uint16_t pAddressDataRegister, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout)
	{
		HAL_StatusTypeDef _status = HAL_BUSY;

		//check if device is ready
		do {
			_status = HAL_I2C_IsDeviceReady(_i2c_port, _device_address,5,timeout);
		} while(_status == HAL_BUSY);

		//only try to read data, when device is ready
		if(_status == HAL_OK) {
			do {
				_status = HAL_I2C_Mem_Read(_i2c_port, _device_address, pAddressDataRegister, sizeAddressData, pData, sizeData, timeout);
			} while(_status == HAL_BUSY);
		}

		return _status;
	}


} /* namespace eLSA */
