/*
 * GPSSensorL80M39.cpp
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#include "sensors/GPSSensorL80M39.h"
#include <sstream>
#include <iomanip>

namespace eLSA {
namespace sensors {

const std::string GPSSensorL80M39::PMTK_SET_NMEA_OUTPUT("PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
const std::string GPSSensorL80M39::PMTK_TXT_MSG("PMTK011,MTKGPS");
const std::string GPSSensorL80M39::PMTK_FULL_COLD_START("PMTK104");
const std::string GPSSensorL80M39::PMTK_COLD_START("PMTK103");
const std::string GPSSensorL80M39::PMTK_WARM_START("PMTK102");
const std::string GPSSensorL80M39::PMTK_HOT_START("PMTK101");
const uint8_t GPSSensorL80M39::GPRMC_LATITUDE_FIELD_INDEX = 3;
const uint8_t GPSSensorL80M39::GPRMC_LONGITUDE_FIELD_INDEX = 5;

GPSSensorL80M39::GPSSensorL80M39(UART_HandleTypeDef* handle) {
	this->handle = handle;

	send(PMTK_SET_NMEA_OUTPUT);
	std::string acknowledgementString = recieve();

	send(PMTK_WARM_START);
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

eLSA::sensors::GPSPoint_t GPSSensorL80M39::getGPSPoint() {
	std::string dataString = recieve();

	std::vector<std::string> splittedDataString = split(dataString);
	int size = splittedDataString.size();

	std::string test = splittedDataString[0];
	std::string latitudeString = splittedDataString[GPRMC_LATITUDE_FIELD_INDEX];
	std::string longitudeString = splittedDataString[GPRMC_LONGITUDE_FIELD_INDEX];

	eLSA::sensors::GPSPoint_t packet;

	if(latitudeString.size() == 0) {
		packet.latitude = 0.0f;
		packet.longitude = 0.0f;
	}
	else {
		std::stringstream stream;
		stream << latitudeString << longitudeString;
		stream >> packet.latitude;
		stream >> packet.longitude;
	}

	return packet;
}

std::vector<std::string> GPSSensorL80M39::split(std::string dataString) {

	std::vector<std::string> splittedStrings;
	const char* c_dataString = dataString.c_str();
	uint8_t dataStringLength = dataString.size();
	uint8_t start = 0;
	uint8_t length;

	for(int i = 0; i < dataStringLength; i++) {
		if(c_dataString[i] == ',') {

			length = i - start;

			if(length == 0) {
				splittedStrings.push_back(std::string());
			}
			else {
				splittedStrings.push_back(std::string(&c_dataString[start], length));
			}

			start = i + 1;
		}
	}

	length = dataStringLength - start;

	//Append the end of the string to the vector
	if(dataStringLength != start) {
		splittedStrings.push_back(std::string(&c_dataString[start], length));
	}

	return splittedStrings;
}

}//namespace sensors
}//namespace eLSA
