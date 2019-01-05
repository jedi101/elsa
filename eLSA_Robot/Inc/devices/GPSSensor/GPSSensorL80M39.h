/*
 * GPSSensorL80M39.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#ifndef GPSSENSORL80M39_H_
#define GPSSENSORL80M39_H_

#include "devices/GPSInterface/GPSPacket.h"
#include "devices/GPSInterface/IGPSSensor.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <string>

namespace device {

class GPSSensorL80M39 : public eLSA::IGPSSensor {
	public:
		GPSSensorL80M39(UART_HandleTypeDef* handle);
		virtual ~GPSSensorL80M39();
		eLSA::GPSPacket getGPSPacket();
		std::string recieve();
		void send(std::string dataString);

	private:
		UART_HandleTypeDef* handle;
};

}

#endif /* GPSSENSORL80M39_H_ */
