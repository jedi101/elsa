/*
 * AccelerometerADXL345.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef DEVICES_SENSORS_ACCELEROMETERADXL345_H_
#define DEVICES_SENSORS_ACCELEROMETERADXL345_H_

#include <sensors/ISensor3Axis.h>

namespace eLSA {
namespace sensors {

class AccelerometerADXL345 : public ISensor3Axis {
public:
	AccelerometerADXL345();
	virtual ~AccelerometerADXL345();
};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_ACCELEROMETERADXL345_H_ */
