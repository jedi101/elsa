/*
 * GPSSensorL80M39.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#ifndef GPSSENSORL80M39_H_
#define GPSSENSORL80M39_H_

#include <sensors/GPSPoint.h>
#include "sensors/IGPSSensor.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <string>
#include <vector>

namespace eLSA {
namespace sensors {

class GPSSensorL80M39 : public eLSA::sensors::IGPSSensor {
	public:
		GPSSensorL80M39(UART_HandleTypeDef* handle);
		virtual ~GPSSensorL80M39();
		eLSA::sensors::GPSPoint_t getGPSPoint();
		std::string recieve();
		void send(std::string dataString);
		std::vector<std::string> split(std::string dataString);

	private:
		UART_HandleTypeDef* handle;
};

}//namespace sensors
}//namespace eLSA

#endif /* GPSSENSORL80M39_H_ */
