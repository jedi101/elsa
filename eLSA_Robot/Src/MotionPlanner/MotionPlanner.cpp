/*
 * MotionPlanner.cpp
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#include <MotionPlanner/MotionPlanner.h>

namespace eLSA {
namespace motionPlanner {

MotionPlanner& MotionPlanner::instance(void) {
	static MotionPlanner _instance;
	return _instance;
}

void MotionPlanner::addWaypoint(sensors::GPSPoint_t waypoint){

}

void MotionPlanner::addListOfWaypoints(std::deque<sensors::GPSPoint_t> waypoints){

}

void MotionPlanner::resetWaypointQueue(void){

}

void MotionPlanner::reset(void){

}

void MotionPlanner::pause(void){

}

void MotionPlanner::run(void){

}

} /* namespace sensors */
} /* namespace eLSA */
