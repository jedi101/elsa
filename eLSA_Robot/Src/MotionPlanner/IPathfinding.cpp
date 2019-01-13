/*
 * IPathfinding.cpp
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#include <MotionPlanner/IPathfinding.h>

namespace eLSA {
namespace motionPlanner {

	void IPathfinding::setDataInterface(pathfindingData_t* dataInterface) {
		if(dataInterface) {
			_dataInterface = dataInterface;
		} else {
			throw "invalid parameter";
		}
	}

} /* namespace motionPlanner */
} /* namespace eLSA */
