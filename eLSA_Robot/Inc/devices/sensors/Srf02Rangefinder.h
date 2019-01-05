
#ifndef DEVICES_SENSORS_SRF02RANGEFINDER_H_
#define DEVICES_SENSORS_SRF02RANGEFINDER_H_

#include <comDevices/StmI2cDevice.h>
#include "comDevices/IComDriver.h"

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
class ISrf02Rangefinder {

public:
	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 */
	virtual int getDistanceInches() = 0;

	/**
	 * @brief This method shall return the measured distance to a possible object in centimeters (rounded)
	 */
	virtual int getDistanceCentimeters() = 0;

	/**
	 * @brief This method shall return the measured distance to a possible object in microseconds (rounded)
	 */
	virtual int getDistanceMicroseconds() = 0;

	/**
	 * @brief This method shall force an autotune of the sensor (which the SRF02 usually automatically runs during init)
	 */
	virtual int forceAutotune() = 0;

	/**
	 * @brief This method shall use the burst functionality of the SRF02.
	 * This emits a short 40kHz burst without using it to measure a distance (quasi an ultrasonic beacon)
	 */
	virtual int emitBurst40kHz() = 0;

	/**
	 * @brief This method determines wether the measured distance falls below given threshold (given in inches)
	 */
	virtual int isDistanceLowerInches(int threshold);

	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 */
	virtual int isDistanceLowerCentimeters(int threshold);

	/**
	 * @brief This method shall return the measured distance to a possible object in imperial inches (rounded)
	 */
	virtual int isDistanceLowerMicroseconds(int threshold);

	static const uint8_t _cmdQueryMeasurementInches = 0x50;
	static const uint8_t _cmdQueryMeasurementCentimeters = 0x51;
	static const uint8_t _cmdQueryMeasurementMicroseconds = 0x52;
	static const uint8_t _cmdSerialGetMeasurement = 0x5E;
	static const uint32_t _delayMeasurementMilliseconds = 70;

};


/**
 * SRF02Rangefinder.h
 *
 * @author Tobias Koppmann
 * @date 11/21/2018
 *
 * @brief This class is an implementation of the ISrf02Rangefinder interface for the I2C bus.
 */
class Srf02RangefinderI2c : public ISrf02Rangefinder{

public:
	Srf02RangefinderI2c(eLSA::hwInterfaces::StmI2cDevice* hwInterface);
	int getDistanceInches();
	int getDistanceCentimeters();
	int getDistanceMicroseconds();
	int forceAutotune();
	int emitBurst40kHz();
	int setHwInterface(eLSA::hwInterfaces::StmI2cDevice* hwInterface);
	int isDistanceLowerInches(int threshold);
	int isDistanceLowerCentimeters(int threshold);
	int isDistanceLowerMicroseconds(int threshold);

private:
	static const uint8_t _i2cCmdRegister = 0x00;
	static const uint8_t _i2cRangeHighByte = 0x02;
	static const uint8_t _i2cRangeLowByte = 0x03;

	int getDistance(const uint8_t* queryType);

	eLSA::hwInterfaces::StmI2cDevice* _i2cInterface;
};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_SRF02RANGEFINDER_H_ */
