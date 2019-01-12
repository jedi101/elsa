
#ifndef DEVICES_SENSORS_SRF02RANGEFINDER_H_
#define DEVICES_SENSORS_SRF02RANGEFINDER_H_

#include <cstdint>
#include <comDevices/IComDriver.h>
#include <comDevices/StmI2cDevice.h>
#include <sensors/IDistanceSensor.h>

namespace eLSA {
namespace sensors {

static const uint32_t I2C_DEFAULT_TIMEOUT = 1000;

/**
 * SRF02Rangefinder.h
 *
 * @author Tobias Koppmann
 * @date 11/21/2018
 *
 * @brief This interface provides an abstraction of the SRF02 ultrasonic rangefinding device which can then be implemented.
 * for various hardware interfaces.
 */
class ISrf02Rangefinder: public IDistanceSensor {

public:

	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 * @return The distance in inches
	 */
	unsigned int getDistanceInInches(void);

	/**
	 * @brief This method shall return the measured distance to a possible object in centimeters (rounded)
	 * @return The distance in centimeters
	 */
	unsigned int getDistanceInCentimeters(void);

	/**
	 * @brief This method shall return the measured distance to a possible object in microseconds (rounded)
	 * @return The distance in microseconds
	 */
	unsigned int getDistanceInMicroseconds(void);

	/**
	 * @brief This method determines wether the measured distance falls below given threshold (given in inches)
	 * @param threshold The threshold against which the measurement is checked
	 * @return 0 if distance is greater or equal, 1 if distance is lower
	 */
	uint8_t isDistanceLowerInInches(unsigned int threshold);

	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 */
	uint8_t isDistanceLowerInCentimeters(unsigned int threshold);

	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 */
	uint8_t isDistanceLowerInMicroseconds(unsigned int threshold);

protected:
	virtual unsigned int getDistance(const uint8_t* queryType) = 0;

	const uint8_t _cmdQueryMeasurementInches = 0x50;
	const uint8_t _cmdQueryMeasurementCentimeters = 0x51;
	const uint8_t _cmdQueryMeasurementMicroseconds = 0x52;
	const uint8_t _cmdSerialGetMeasurement = 0x5E;
	const uint32_t _delayMeasurementMilliseconds = 70;
	const uint8_t _i2cCmdRegister = 0x00;
	const uint8_t _i2cRangeHighByte = 0x02;
	const uint8_t _i2cRangeLowByte = 0x03;
};

class Srf02RangefinderI2C : public ISrf02Rangefinder {
public:
	Srf02RangefinderI2C(comDevices::StmI2cDevice* hwInterface);

private:
	unsigned int getDistance(const uint8_t* queryType);
	comDevices::StmI2cDevice* _i2cInterface;

};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_SRF02RANGEFINDER_H_ */
