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
namespace comDevices{

/**
 * @author Tobias Koppmann
 * @date 09.12.2018
 *
 * @brief This interface is used to generalise a communication device and provide unified hardware abstraction as specified for
 * the eLSA system
 */ 
class IComDriver {

public:
	/**
    * @brief This method is used to read data from a hardware communication interface
    * @param pData Pointer a data buffer where the read data is stored
	* @param sizeData Size of the data buffer given on pData
    * @return  -1 on error or 0 if operation is ok
    */
	virtual int readData(uint8_t* pData, uint16_t sizeData) = 0;
	
	/**
    * @brief This method is used to write data to a remote device via the communication interface
    * @param pData Pointer to a data buffer where the write data is stored
	* @param sizeData Size of the data buffer given on pData
    * @return  -1 on error or 0 if operation is ok
    */
	virtual int writeData(uint8_t* pData, uint16_t sizeData) = 0;

	/**
    * @brief This method is used to set the timeout of the communication interface
    * @param time An integer value giving the timeout
    */
	virtual void setConnectionTimeout(uint32_t time) = 0;
};

} /* namespace hw_interfaces */
} /* namespace eLSA */

#endif /* DEVICES_COMDEVICES_ICOMDRIVER_H_ */
