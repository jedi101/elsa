/*
 * IGPSSensor.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#ifndef IGPSSENSOR_H_
#define IGPSSENSOR_H_

namespace eLSA {
namespace sensors {

/**
 * @author Richard Leikam
 * @date 04.12.2018
 * This struct is used to represent a GPS position
 */
struct GPSPoint_t {
	double longitude; ///< The longitude given in dddmm.mmmmmm where d=degree and m=minutes
	double latitude; ///< ///< The latitude given in ddmm.mmmmmm where d=degree and m=minutes

	GPSPoint_t(double longitude=0.0, double latitude=0.0)
		:longitude{longitude}, latitude{latitude} {}

	// assignment operator modifies object, therefore non-const
	GPSPoint_t& operator=(const GPSPoint_t& other)
	{
		longitude=other.longitude;
		latitude=other.latitude;
		return *this;
	}

    // add operation doesn't modify object, therefore const
	GPSPoint_t operator+(const GPSPoint_t& other) const
    {
        return GPSPoint_t(other.longitude+longitude, other.latitude+latitude);
    }

    // equality comparison doesn't modify object, therefore const.
     bool operator==(const GPSPoint_t& other) const
     {
         return (longitude == other.longitude && latitude == other.latitude);
     }

} ;

/**
 * @author Tobias Koppmann
 * @date 16.01.2019
 * This type trait is used to check if variable is of GPSPoint_t -> wrong type
 */
template <typename T>
struct is_GPSPoint
{static const bool value = false;};

/**
 * @author Tobias Koppmann
 * @date 16.01.2019
 * This type trait is used to check if variable is of GPSPoint_t -> right type
 */
template <>
struct is_GPSPoint<GPSPoint_t>
{static const bool value = true;};

/**
 * @author Richard Leikam
 * @date 04.12.2018
 *
 * @brief This interface is used to generalise a GPS sensor and provide a unified hardware abstraction as specified for
 * the eLSA system
 */ 
class IGPSSensor {
public:
    /**
    * @brief This method is used to get the current GPS position as measured by the sensor
    * @return A GPS-Point struct variable containing longitude as well as latitude
    */
	virtual GPSPoint_t getGPSPoint() = 0;
};

}//namespace sensors
}//namespace eLSA
#endif /* IGPSSENSOR_H_ */
