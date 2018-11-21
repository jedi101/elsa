/*
 * I2CDevice.h
 *
 *  Created on: 21.11.2018
 *      Author: Tobias
 */

#ifndef ELSA_I2CDEVICE_H_
#define ELSA_I2CDEVICE_H_

#include <cstdint>
#include "i2c.h"

namespace eLSA {

class STM_I2C_Device /*: I2C_Device*/ {
public:
	STM_I2C_Device();
	STM_I2C_Device(I2C_HandleTypeDef* i2c_port, uint16_t device_address);
	virtual ~STM_I2C_Device();
	unsigned int writeCommand(uint16_t pAddressCommand, uint16_t sizeAddressCommand, uint8_t* pCommand, uint16_t sizeCommand, uint32_t timeout);
	unsigned int writeData(uint16_t pAddressData, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout);
	unsigned int readData(uint16_t pAddressData, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout);

private:
	I2C_HandleTypeDef* _i2c_port;
	uint16_t _device_address;
};

} /* namespace eLSA */

#endif /* ELSA_I2CDEVICE_H_ */
