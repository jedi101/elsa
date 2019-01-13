/*
 * Bug1.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_BUG1_H_
#define MOTIONPLANNER_BUG1_H_

#include <MotionPlanner/IPathfinding.h>

namespace eLSA {
namespace motionPlanner {

class Bug1: public IPathfinding {
public:
	Bug1();
	virtual ~Bug1();
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_BUG1_H_ */
