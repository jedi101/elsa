/*
 * MagnetometerHMC5883L.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef DEVICES_SENSORS_MAGNETOMETERHMC5883L_H_
#define DEVICES_SENSORS_MAGNETOMETERHMC5883L_H_

#include <sensors/ISensor3Axis.h>

namespace eLSA {
namespace sensors {

class MagnetometerHMC5883L {
public:
	MagnetometerHMC5883L();
	virtual ~MagnetometerHMC5883L();
};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_MAGNETOMETERHMC5883L_H_ */
