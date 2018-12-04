/*
 * ComDevice.h
 *
 *  Created on: 04.12.2018
 *      Author: Tobias
 */

#ifndef DEVICES_COMDEVICES_ICOMDRIVER_H_
#define DEVICES_COMDEVICES_ICOMDRIVER_H_

#include <cstdint>

namespace eLSA {

namespace hwInterfaces{

class IComDriver {

public:
	virtual int readData(uint8_t* pData, uint16_t sizeData) = 0;
	virtual int writeData(uint8_t* pData, uint16_t sizeData) = 0;
	virtual void setConnectionTimeout(uint32_t time) = 0;
};

} /* namespace hw_interfaces */
} /* namespace eLSA */

#endif /* DEVICES_COMDEVICES_ICOMDRIVER_H_ */
