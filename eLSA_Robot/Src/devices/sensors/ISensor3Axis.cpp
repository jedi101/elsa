/*
 * ISensor3Axis.cpp
 *
 *  Created on: 03.01.2019
 *      Author: Tobias
 */

#include <sensors/ISensor3Axis.h>

namespace eLSA {
namespace sensors {

	void ISensor3Axis::setOffset(vector_t offset){
		_offset = offset;
	}

	vector_t ISensor3Axis::getOffset(void){
		return _offset;
	}

} /* namespace sensors */
} /* namespace eLSA */
