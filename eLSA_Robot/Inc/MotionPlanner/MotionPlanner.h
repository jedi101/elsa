/*
 * MotionPlanner.h
 *
 *  Created on: 28.12.2018
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_MOTIONPLANNER_H_
#define MOTIONPLANNER_MOTIONPLANNER_H_

#include <deque>
#include <sensors/IGPSSensor.h>
#include <MotionPlanner/MotionPlannerGeneral.h>
#include <MotionPlanner/MotionPlanner.h>
#include <MotionPlanner/IPathfinding.h>

namespace eLSA {
namespace motionPlanner {

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 * The central management entity for the eLSA-robot system.
 * Due to the "central" aspect of the class it is implemented as a singleton.
 * In this case a static singleton instance is used since the objects lifespan is the complete system runtime
 */
class MotionPlanner {
public:

	/**
	 * @brief The getter for the singleton instance of the MotionPlanner
	 * @return The singleton instance
	 */
	static MotionPlanner& instance(void);

	/**
	 * @brief This method adds a waypoint to the internal queue
	 * @param waypoint A waypoint which will be added to the back of the queue
	 */
	void addWaypoint(sensors::GPSPoint_t waypoint);

	/**
	 * @brief This method adds multiple waypoints to the internal queue in the order in which they are stored
	 * @param waypoints A queue of waypoints which will be appended to the back of the queue
	 */
	void addListOfWaypoints(std::deque<sensors::GPSPoint_t> waypoints);

	/**
	 * @brief This method resets the internal waypoint queue
	 */
	void resetWaypointQueue(void);

	/**
	 * @brief This method resets the complete MotionPlanner
	 */
	void reset(void);

	/**
	 * @brief This method pauses the motion system of the robot
	 */
	void pause(void);

	/**
	 * @brief This method runs the internal logic and thus the movement of the robot
	 */
	void run(void);

	/**
	 * @brief This method sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	void setDataInterface(pathfindingData_t* dataInterface);

private:
	MotionPlanner();
	MotionPlanner(const MotionPlanner&);

	std::deque<sensors::GPSPoint_t> _waypoints;
	IPathfinding* _pathfindingAlgorithm;
	pathfindingData_t* _pathfindingDataInterface;

};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_MOTIONPLANNER_H_ */
