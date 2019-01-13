/*
 * Bug2.h
 *
 *  Created on: 13.01.2019
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_BUG2_H_
#define MOTIONPLANNER_BUG2_H_

#include <MotionPlanner/IPathfinding.h>

namespace eLSA {
namespace motionPlanner {

class Bug2: public IPathfinding {
public:
	Bug2();
	virtual ~Bug2();
};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_BUG2_H_ */
