/*
 * MotionPlanner.h
 *
 *  Created on: 13.01.2019
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

class MotionPlanner {
public:
	MotionPlanner();
	virtual ~MotionPlanner();

	void addWaypoint(sensors::GPSPoint_t waypoint);
	void addListOfWaypoints(std::deque<sensors::GPSPoint_t> waypoints);
	void resetWaypointQueue(void);
	void reset(void);
	void pause(void);
	void run(void);

private:
	std::deque<sensors::GPSPoint_t> _waypoints;
	IPathfinding* _pathfindingAlgorithm;
	pathfindingData_t* _pathfindingDataInterface;
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_MOTIONPLANNER_H_ */
