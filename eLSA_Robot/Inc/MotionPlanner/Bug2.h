/*
 * Bug2.h
 *
 *  Created on: 28.12.2018
 *      Author: Tobias
 */

#ifndef MOTIONPLANNER_BUG2_H_
#define MOTIONPLANNER_BUG2_H_

#include <MotionPlanner/IPathfinding.h>
#include <cstdint>
#include <sensors/IGPSSensor.h>
#include <vector>

namespace eLSA {
namespace motionPlanner {

typedef enum {
	IDLE,
	MOVE_ON_MLINE,
	FOLLOW_BOUNDARY,
	ERROR
} bug2State_t;

/**
 * @author Tobias Koppmann
 * @date 28.12.2018
 *
 */
class Bug2: public IPathfinding {
public:

	/**
	 * @brief The constructor sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	Bug2(pathfindingData_t* dataInterface);

	/**
	 * @brief Invoking this method runs the algorithm
	 */
	void runAlgorithm(void);

	/**
	 * @brief This method sets the datainterface on which the Pathfinder communicates with the MotionPlanner
	 * @param dataInterface Pointer to the data interface
	 */
	void resetAlgorithm(void);

private:
	bug2State_t _currentState;
	std::vector<sensors::GPSPoint_t> _encounteredObstaclesPositions;
	std::vector<sensors::GPSPoint_t> _mLineReentrancePositions;

	uint16_t getBearingBetweenTwoCoordinates(sensors::GPSPoint_t point_1, sensors::GPSPoint_t point_2);
	double crossProductCurrentPosAndMline(void);
	uint8_t isCurrentPositionOnMLine(void);
	int isCurrentPositionLeftOrRightOfMLine(void);
	void moveAlongMline(void);
	void followBoundary(void);

};

} /* namespace motionPlanner */
} /* namespace eLSA */

#endif /* MOTIONPLANNER_BUG2_H_ */
