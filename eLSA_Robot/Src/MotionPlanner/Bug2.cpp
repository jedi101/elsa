/*
 * Bug2.cpp
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#include <MotionPlanner/Bug2.h>
#include <cmath>
#include <typeinfo>

namespace eLSA {
namespace motionPlanner {

Bug2::Bug2(pathfindingData_t* dataInterface)
	: IPathfinding{dataInterface}
{

}

void Bug2::runAlgorithm(void){

}

void Bug2::resetAlgorithm(void){

}

uint16_t Bug2::getBearingBetweenTwoCoordinates(sensors::GPSPoint_t point_1, sensors::GPSPoint_t point_2) {

	//delta between longitudes (length of adjacent side to bearing angle)
	double deltaLongitude = point_2.longitude - point_1.longitude;

	//delta between latitudes (length of opposite side to bearing angle)
	double deltaLatitude = point_2.latitude - point_1.latitude;

	//
	double yComponent = std::sin(deltaLongitude) * std::cos(point_2.latitude);

	double xComponent = (std::cos(point_1.latitude) * std::sin(point_2.latitude))
							- (std::sin(point_1.latitude) * std::cos(point_2.latitude) * std::cos(deltaLatitude));

	double bearing = std::atan2(yComponent, xComponent);
	bearing = (bearing * M_PI) / 180.0;// radians to degrees
	bearing = (((uint16_t)bearing + 360) % 360 );

	return bearing;
}

double Bug2::crossProductCurrentPosAndMline(void) {
	// distances in longitude and latitude on mline end points
	double deltaLongitudeMLine = this->_dataInterface->in.currentPosition.longitude - this->_dataInterface->in.startPosition.longitude;
	double deltaLatitudeMLine = this->_dataInterface->in.currentPosition.latitude - this->_dataInterface->in.startPosition.latitude;

	// distances in longitude and latitude between starting position and current position
	double deltaLongitudeCurrent = this->_dataInterface->in.currentPosition.longitude - this->_dataInterface->in.startPosition.longitude;
	double deltaLatitudeCurrent = this->_dataInterface->in.currentPosition.latitude - this->_dataInterface->in.startPosition.latitude;

	// cross product
	return (deltaLongitudeCurrent * deltaLatitudeMLine) - (deltaLatitudeCurrent * deltaLongitudeMLine);
}

uint8_t Bug2::isCurrentPositionOnMLine(void) {

	uint8_t returnValue = 0;
	// distances in longitude and latitude between starting position and current position
	double deltaLongitudeCurrent = this->_dataInterface->in.currentPosition.longitude - this->_dataInterface->in.startPosition.longitude;
	double deltaLatitudeCurrent = this->_dataInterface->in.currentPosition.latitude - this->_dataInterface->in.startPosition.latitude;
	// distances in longitude and latitude on mline end points
	double deltaLongitudeMLine = this->_dataInterface->in.currentPosition.longitude - this->_dataInterface->in.startPosition.longitude;
	double deltaLatitudeMLine = this->_dataInterface->in.currentPosition.latitude - this->_dataInterface->in.startPosition.latitude;

	//if point lies on m-line vector check if point also is between start and target point
	if(crossProductCurrentPosAndMline() == 0.0) {

		// is line more tilted towards latitude(vertical) or horizontal(longitude) direction?
		if (std::abs(deltaLongitudeCurrent) >= std::abs(deltaLatitudeCurrent)) {
			//more tilted towards longitude
			returnValue =
					// calculating with numerical smaller target (going "backwards")?
					deltaLongitudeMLine > 0 ?
					  (this->_dataInterface->in.startPosition.longitude <= this->_dataInterface->in.currentPosition.longitude) && (this->_dataInterface->in.currentPosition.longitude <= this->_dataInterface->in.targetPosition.longitude)
					: (this->_dataInterface->in.targetPosition.longitude <= this->_dataInterface->in.currentPosition.longitude) && (this->_dataInterface->in.currentPosition.longitude <= this->_dataInterface->in.startPosition.longitude);
		} else {
			//more tilted towards latitude
			returnValue =
					// calculating with numerical smaller target (going "backwards")?
					deltaLatitudeMLine > 0 ?
					  (this->_dataInterface->in.startPosition.latitude <= this->_dataInterface->in.currentPosition.latitude) && (this->_dataInterface->in.currentPosition.latitude <= this->_dataInterface->in.targetPosition.latitude)
					: (this->_dataInterface->in.targetPosition.latitude <= this->_dataInterface->in.currentPosition.latitude) && (this->_dataInterface->in.currentPosition.latitude <= this->_dataInterface->in.startPosition.latitude);
		}
	}

	return returnValue;

}

int Bug2::isCurrentPositionLeftOrRightOfMLine(void) {

	int returnValue;
	double crossProduct = crossProductCurrentPosAndMline();
	double deltaLongitudeMLine = this->_dataInterface->in.currentPosition.longitude - this->_dataInterface->in.startPosition.longitude;

	if(crossProduct == 0.0) {	// position is colinear with m-line vector
		returnValue = 0;
	} else if(deltaLongitudeMLine < 0) { 	//moving "backwards" (bigger values -> smaller values)
		if(crossProduct > 0) {
			returnValue = -1;	// position is on the left of m-line in relation to movement direction
		} else {
			returnValue = 1;	// position is on the right of m-line in relation to movement direction
		}
	} else {								//moving "forwards" (smaller values -> bigger values)
		if(crossProduct > 0) {
			returnValue = 1;	// position is on the right of m-line in relation to movement direction
		} else {
			returnValue = -1;	// position is on the left of m-line in relation to movement direction
		}
	}

	return returnValue;
}

void Bug2::moveAlongMline(void) {
	;
}

} /* namespace motionPlanner */
} /* namespace eLSA */
