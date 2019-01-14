/*
 * IPathfinding.h
 *
 *  Created on: 28.12.2018
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_IPATHFINDING_H_
#define MOTIONPLANNER_IPATHFINDING_H_

#include <MotionPlanner/MotionPlannerGeneral.h>

namespace eLSA {
namespace motionPlanner {

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 * An interface for a pathfinding algorithm used by the MotionPlanner
 */
class IPathfinding {
public:

	/**
	 * @brief The constructor sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	IPathfinding(pathfindingData_t* dataInterface);

	/**
	 * @brief Invoking this method runs the algorithm
	 */
	virtual void runAlgorithm(void) = 0;

	/**
	 * @brief This method resets the internal state and data
	 */
	virtual void resetAlgorithm(void) = 0;

	/**
	 * @brief This method sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	void setDataInterface(pathfindingData_t* dataInterface);

protected:
	pathfindingData_t* _dataInterface;
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_IPATHFINDING_H_ */
