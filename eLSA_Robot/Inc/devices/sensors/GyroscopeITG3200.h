/*
 * GyroscopeITG3200.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef DEVICES_SENSORS_GYROSCOPEITG3200_H_
#define DEVICES_SENSORS_GYROSCOPEITG3200_H_

#include <sensors/ISensor3Axis.h>

namespace eLSA {
namespace sensors {

class GyroscopeITG3200 {
public:
	GyroscopeITG3200();
	virtual ~GyroscopeITG3200();
};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_GYROSCOPEITG3200_H_ */
