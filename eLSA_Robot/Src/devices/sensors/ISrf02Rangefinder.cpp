/*
 * SRF02Rangefinder.cpp
 *
 *  Created on: 10.12.2018
 *      Author: Tobias
 */

#include <sensors/ISrf02Rangefinder.h>

namespace eLSA {
namespace sensors {

unsigned int ISrf02Rangefinder::getDistanceInInches(void)
{
	try {
		return getDistance(&_cmdQueryMeasurementInches);
	} catch(...) {
		throw;
	}

}

unsigned int ISrf02Rangefinder::getDistanceInCentimeters(void)
{
	try {
		return getDistance(&_cmdQueryMeasurementCentimeters);
	} catch(...) {
		throw;
	}
}

unsigned int ISrf02Rangefinder::getDistanceInMicroseconds(void)
{
	try {
		return getDistance(&_cmdQueryMeasurementMicroseconds);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInCentimeters(unsigned int threshold)
{
	try {
		return (getDistanceInCentimeters() < threshold);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInInches(unsigned int threshold)
{
	try {
		return (getDistanceInInches() < threshold);
	} catch(...) {
		throw;
	}
}

uint8_t ISrf02Rangefinder::isDistanceLowerInMicroseconds(unsigned int threshold)
{
	try {
		return (getDistanceInMicroseconds() < threshold);
	} catch(...) {
		throw;
	}
}

} /* namespace sensors */
} /* namespace eLSA */
