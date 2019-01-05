/*
 * GPSSensorL80M39.cpp
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#include "sensors/GPSSensorL80M39.h"
#include "lib/nematode/nmeaparse/nmea.h"
#include <sstream>
#include <iomanip>

namespace eLSA {
namespace sensors {

GPSSensorL80M39::GPSSensorL80M39(UART_HandleTypeDef* handle) {
	this->handle = handle;
}

GPSSensorL80M39::~GPSSensorL80M39() {
	// TODO Auto-generated destructor stub
}

void GPSSensorL80M39::send(std::string pmtkCommand) {

	uint8_t pmtkCommandSize = pmtkCommand.size();

	//Create checksum
	uint8_t checksum = pmtkCommand[0];
	for(int i = 1; i < pmtkCommandSize; i++) {
		checksum ^= pmtkCommand[i];
	}

	//Convert checksum to hexadecimal representation and concatenate string
	std::stringstream stream("");
	stream << std::setfill('0') << std::setw(2) << std::hex << (int)checksum;
	std::string transmittingDataString = std::string("$") + pmtkCommand + "*" + stream.str() + "\xD\xA";

	//Transform pmtkCommand into integer string
	uint8_t transmittingDataStringSize = transmittingDataString.size();
	uint8_t transmittingData[transmittingDataStringSize];
	for(int i = 0; i < transmittingDataStringSize; i++) {
		transmittingData[i] = transmittingDataString[i];
	}

	HAL_UART_Transmit(handle, transmittingData, transmittingDataStringSize, 6000);
}

std::string GPSSensorL80M39::recieve() {
	std::string data;
	uint8_t recievedCharacter;
	bool end = false;

	while(!end) {
		HAL_UART_Receive(handle, &recievedCharacter, 1, 6000);

		if(recievedCharacter == 10) {
			end = true;
		}

		data += static_cast<char>(recievedCharacter);
	}

	return data;
}

eLSA::sensors::GPSPacket GPSSensorL80M39::getGPSPacket() {

	nmea::NMEAParser parser;
	nmea::GPSService gpsservice(parser);



	float longitude = 0.0f;
	float latitude = 0.0f;

	eLSA::sensors::GPSPacket packet(longitude, latitude);
	return packet;
}

}//namespace sensors
}//namespace eLSA
