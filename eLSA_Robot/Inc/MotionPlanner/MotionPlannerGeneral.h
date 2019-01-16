/*
 * MotionPlanner.h
 *
 *  Created on: 28.12.2018
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_MOTIONPLANNERGENERAL_H_
#define MOTIONPLANNER_MOTIONPLANNERGENERAL_H_

#include <sensors/IGPSSensor.h>
#include <cstdint>

namespace eLSA {
namespace motionPlanner {

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 * This struct is used to provide data to a pathfinding algorithm
 */
struct pathfindingDataIn_t {
    sensors::GPSPoint_t currentPosition; 	///< The current GPS position of the robot
    float currentHeading; 					///< The current heading of the robot
    sensors::GPSPoint_t startPosition; 		///< The position from which the pathfinding starts
    sensors::GPSPoint_t targetPosition; 	///< The position to which the robot is meant to move
    uint8_t isObstacleAhead;				///< Boolean value telling if a obstacle is sensed
};

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 * This struct is used to get commands and states from a pathfinding algorithm
 */
struct pathfindingDataOut_t{

};

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 * This struct is used to share data between a pathfinding algorithm and a superordinate instance
 */
typedef struct {
	struct pathfindingDataIn_t in; ///< data TO the pathfinding algorithm
	struct pathfindingDataOut_t out; ///< data FROM the pathfinding algorithm
}pathfindingData_t;

} //namespace motionplanner
} //namespace eLSA

#endif /* MOTIONPLANNER_MOTIONPLANNERGENERAL_H_ */
