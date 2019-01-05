/*
 * IGPSSensor.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#include "devices/GPSInterface/GPSPacket.h"

#ifndef IGPSSENSOR_H_
#define IGPSSENSOR_H_

namespace eLSA {

class IGPSSensor {
public:
	virtual GPSPacket getGPSPacket() = 0;
};

}

#endif /* IGPSSENSOR_H_ */
