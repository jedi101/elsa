
#ifndef ELSA_I2CDEVICE_H_
#define ELSA_I2CDEVICE_H_

#include <comDevices/IComDriver.h>
#include <cstdint>
#include "i2c.h"

namespace eLSA {
namespace hwInterfaces{

/**
 * @author Tobias Koppmann
 * @date 11/21/2018
 *
 * @brief This class encapsulates a STM32 HAL I2C memory interface in an eLSA specific I2C device.
 *  A device object is bound to a specific bus address and therefore representing a single device.
 *  The class provides standard read/write methods for common I2C operations.
 */
class StmI2cDevice : public hwInterfaces::IComDriver {
public:

	//delete the standard constructor, so that it is impossible to create unusable objects
	StmI2cDevice() = delete;

	/**
	 * @param i2c_port A STM32 HAL handle describing the device
	 * @param device_address The bus address of the device which an object of this class is representing
	 */
	StmI2cDevice(I2C_HandleTypeDef* i2cPort, uint16_t deviceAddress);

	/**
	 * Just a standard deconstructor
	 */
	virtual ~StmI2cDevice();

	/**
	 * @param pRegisterAddress Pointer to a variable containing the address value to which is written
	 * @param sizeRegisterAddress Size of the given address value. This value is explicit to make 11Bit I2C adressing available
	 */
	int setDeviceRegisterParams(uint16_t pRegisterAddress, uint16_t sizeRegisterAddress);

	/**
	 * @param time Desired connection timeout in milliseconds
	 */
	void setConnectionTimeout(uint32_t time);

	/**
	 * @param pData Pointer to the start address of the data which is written
	 * @param sizeData Size of the data block which is written
	 */
	int writeData(uint8_t* pData, uint16_t sizeData);

	/**
	 * @param pData Pointer to the start address of the data buffer to which the read data is written
	 * @param sizeData Size of the data block which is read
	 */
	int readData(uint8_t* pData, uint16_t sizeData);

private:
	I2C_HandleTypeDef* _i2cPort;
	uint16_t _deviceAddress;
	uint16_t _pRegisterAddress;
	uint16_t _sizeRegisterAddress;
	uint32_t _timeout = 100;
};

} /* namespace hwInterfaces */
} /* namespace eLSA */

#endif /* ELSA_I2CDEVICE_H_ */
