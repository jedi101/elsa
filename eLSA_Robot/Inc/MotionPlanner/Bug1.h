/*
 * Bug1.h
 *
 *  Created on: 28.12.2018
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_BUG1_H_
#define MOTIONPLANNER_BUG1_H_

#include <MotionPlanner/IPathfinding.h>

namespace eLSA {
namespace motionPlanner {

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 *
 */
class Bug1: public IPathfinding {
public:

	/**
	 * @brief The constructor sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	Bug1(pathfindingData_t* dataInterface);

	/**
	 * @brief Invoking this method runs the algorithm
	 */
	void runAlgorithm(void);

	/**
	 * @brief This method sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	void resetAlgorithm(void);
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_BUG1_H_ */
