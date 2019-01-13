/*
 * IPathfinding.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_IPATHFINDING_H_
#define MOTIONPLANNER_IPATHFINDING_H_

#include <MotionPlanner/MotionPlannerGeneral.h>

namespace eLSA {
namespace motionPlanner {

class IPathfinding {
public:
	virtual void runAlgorithm(void) = 0;
	virtual void resetAlgorithm(void) = 0;
	void setDataInterface(pathfindingData_t* dataInterface);

protected:
	pathfindingData_t* _dataInterface;
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_IPATHFINDING_H_ */
