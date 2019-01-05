/*
 * GPSPacket.cpp
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#include <sensors/GPSPacket.h>

namespace eLSA {
namespace sensors {

GPSPacket::GPSPacket(float longitude, float latitude) {
	 this->longitude = longitude;
	 this->latitude = latitude;
}

float GPSPacket::getLongitude() {
	 return longitude;
}

float GPSPacket::getLatitude() {
	 return latitude;
}

} //namespace sensors
} /* namespace eLSA */
