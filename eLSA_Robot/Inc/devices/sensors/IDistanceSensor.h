#ifndef DEVICES_SENSORS_IDISTANCESENSOR_H_
#define DEVICES_SENSORS_IDISTANCESENSOR_H_

#include <cstdint>
#include <comDevices/IComDriver.h>
namespace eLSA {
namespace sensors {

/**
 * @author Tobias Koppmann
 * @date 23.12.2018
 *
 * @brief This interface is used to generalise a distance sensor and provide basic functionality as specified for
 * the eLSA system
 */ 
class IDistanceSensor {
    public:
    	/**
         * @brief This method is used to get the measured distance of the sensor
         * @return The measured distance in centimeters (SI units)
         */
        virtual unsigned int getDistanceInCentimeters(void) = 0;

    	/**
         * @brief This method is used to get the measured distance of the sensor
         * @return The measured distance in inches (imoerial units)
         */
        virtual unsigned int getDistanceInInches(void) = 0;

        /**
         * @brief This is a check method to determine if the measured distance of the sensor is a value below a certain threshold
         *  This method is used for measurements in centimeters (SI-units)
         * @param threshold The threshold in centimeters below which the the method returns true
         * @return  Either 0 if measured distance is over or equal given threshold or 1 if measured distance is below threshold
         */
        virtual uint8_t isDistanceLowerInCentimeters(unsigned int threshold) = 0;
        
        /**
         * @brief This is a check method to determine if the measured distance of the sensor is a value below a certain threshold
         *  This method is used for measurements in inches (imperial)
         * @param threshold The threshold in centimeters below which the the method returns true
         * @return  Either 0 if measured distance is over or equal given threshold or 1 if measured distance is below threshold
         */
        virtual uint8_t isDIstanceLowerInInches(unsigned int threshold) = 0;

};

} // namespace sensors
} // namespace eLSA
#endif /* DEVICES_SENSORS_IDISTANCESENSOR_H_ */
