
#ifndef ELSA_I2CDEVICE_H_
#define ELSA_I2CDEVICE_H_

#include <cstdint>
#include "i2c.h"

namespace eLSA {

/**
 * @author Tobias Koppmann
 * @date 11/21/2018
 *
 * @brief This class encapsulates a STM32 HAL I2C memory interface in an eLSA specific I2C device.
 *  A device object is bound to a specific bus address and therefore representing a single device.
 *  The class provides standard read/write methods for common I2C operations.
 */
class STM_I2C_Device /*: I2C_Device*/ {
public:
	/**
	 * @param i2c_port A STM32 HAL handle describing the device
	 * @param device_address The bus address of the device which an object of this class is representing
	 */
	STM_I2C_Device(I2C_HandleTypeDef* i2c_port, uint16_t device_address);

	/**
	 * Just a standard deconstructor
	 */
	virtual ~STM_I2C_Device();

	/**
	 * @param pAddressCommand Pointer to a variable containing the address value to which is written
	 * @param sizeAddressCommand Size of the given address value. This value is explicit to make 11Bit I2C adressing available
	 * @param pCommand Pointer to a variable containing the command value which is written
	 * @param sizeCommand Size of the command which is written
	 * @param timeout Timeout for the interface in milliseconds
	 */
	unsigned int writeCommand(uint16_t pAddressCommand, uint16_t sizeAddressCommand, uint8_t* pCommand, uint16_t sizeCommand, uint32_t timeout);

	/**
	 * @param pAddressData Pointer to a variable containing the address value to which is written
	 * @param sizeAddressData Size of the given address value. This value is explicit to make 11Bit I2C adressing available
	 * @param pData Pointer to the start address of the data which is written
	 * @param sizeData Size of the data block which is written
	 * @param timeout Timeout for the interface in milliseconds
	 */
	unsigned int writeData(uint16_t pAddressData, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout);

	/**
	 * @param pAddressData Pointer to a variable containing the address value from which is read
	 * @param sizeAddressData Size of the given address value. This value is explicit to make 11Bit I2C adressing available
	 * @param pData Pointer to the start address of the data buffer to which the read data is written
	 * @param sizeData Size of the data block which is read
	 * @param timeout Timeout for the interface in milliseconds
	 */
	unsigned int readData(uint16_t pAddressData, uint16_t sizeAddressData, uint8_t* pData, uint16_t sizeData, uint32_t timeout);

private:
	I2C_HandleTypeDef* _i2c_port;
	uint16_t _device_address;
};

} /* namespace eLSA */

#endif /* ELSA_I2CDEVICE_H_ */
