/*
 * ISensor3Axis.h
 *
 *  Created on: 03.01.2019
 *      Author: Tobias
 */

#ifndef DEVICES_SENSORS_ISENSOR3AXIS_H_
#define DEVICES_SENSORS_ISENSOR3AXIS_H_

namespace eLSA {
namespace sensors {

/**
 * @author Tobias Koppmann
 * @date 03.01.2019
 * This struct stores a 3 dimensional vector in accordance to the three main axes of the robot
 */
struct vector_t{
	float x;	///< The partial vector value related to the X-axis
	float y;	///< The partial vector value related to the Y-axis
	float z;	///< The partial vector value related to the Z-axis

	vector_t(float x=0.0, float y=0.0, float z=0.0)
			:x{x}, y{y}, z{z}
	{}

	// assignment operator modifies object, therefore non-const
	vector_t& operator=(const vector_t& other)
	{
		x=other.x;
		y=other.y;
		z=other.z;
		return *this;
	}

	// add operation doesn't modify object, therefore const
	vector_t operator+(const vector_t& other) const
	{
		return vector_t(other.x+x, other.y+y, other.z+z);
	}

	// equality comparison doesn't modify object, therefore const.
	 bool operator==(const vector_t& other) const
	 {
		 return (x == other.x && y == other.y && z == other.z);
	 }
};

/**
 * @author Tobias Koppmann
 * @date 03.01.2019
 *
 * @brief This interfaces generalizes a 3 axis sensor which exists for a manifold of vectorial physical sizes
 */
class ISensor3Axis {
public:

	/**
	 * @return The vector struct contains all partial value measurements of the sensor
	 */
	virtual vector_t getVector(void) = 0;

	/**
	 * @brief Usually the the initial measurements deviate from reality.
	 * To get realistic measurements an offset is needed.
	 *
	 * @param offset A 3-dimensional offset which will be applied to any further data output on getVector()
	 */
	virtual void setOffset(vector_t offset);

	/**
	 * @return The vector struct contains the offsets used for the measurement matching
	 */
	virtual vector_t getOffset(void);

protected:
	vector_t _offset;

};

} /* namespace sensors */
} /* namespace eLSA */

#endif /* DEVICES_SENSORS_ISENSOR3AXIS_H_ */
