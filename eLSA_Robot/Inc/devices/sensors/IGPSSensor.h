/*
 * IGPSSensor.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#include "sensors/GPSPacket.h"

#ifndef IGPSSENSOR_H_
#define IGPSSENSOR_H_

namespace eLSA {
namespace sensors {

class IGPSSensor {
public:
	virtual GPSPacket getGPSPacket() = 0;
};

}//namespace sensors
}//namespace eLSA
#endif /* IGPSSENSOR_H_ */
