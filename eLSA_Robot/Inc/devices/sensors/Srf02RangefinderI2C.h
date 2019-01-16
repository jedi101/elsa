
#ifndef DEVICES_SENSORS_ISRF02RANGEFINDERI2C_H_
#define DEVICES_SENSORS_ISRF02RANGEFINDERI2C_H_

#include <sensors/ISrf02Rangefinder.h>
#include <comDevices/StmI2cDevice.h>
#include <cstdint>

namespace eLSA {
namespace sensors {

/**
 * SRF02Rangefinder.h
 *
 * @author Tobias Koppmann
 * @date 13.01.2018
 *
 * @brief This class is a concrete implementation for the SrfRangefinder using the I2C interface
 */
class Srf02RangefinderI2C : public ISrf02Rangefinder {
public:

	/**
	 * @param hwInterface The I2C hardware interface which shall be used by the object
	 * @param deviceAddress The 7-Bit address of the device this object represents
	 */
	Srf02RangefinderI2C(comDevices::StmI2cDevice* hwInterface, uint8_t deviceAddress);

private:
	unsigned int getDistance(const uint8_t* queryType);
	comDevices::StmI2cDevice* _i2cInterface;
	uint8_t _i2cAddress;
	const uint8_t _i2cCmdRegister = 0x00;
	const uint8_t _i2cRangeHighByte = 0x02;
	const uint8_t _i2cRangeLowByte = 0x03;

};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_ISRF02RANGEFINDERI2C_H_ */
