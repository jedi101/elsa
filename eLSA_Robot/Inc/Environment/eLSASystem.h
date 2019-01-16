/*
 * eLSASystem.h
 *
 *  Created on: 16.01.2019
 *      Author: Tobias
 */

#ifndef ENVIRONMENT_ELSASYSTEM_H_
#define ENVIRONMENT_ELSASYSTEM_H_

#include <actuators/Motorcontroller.h>
#include <display/DisplaySSD1306.h>
#include <sensors/IDistanceSensor.h>
#include <sensors/ISensor3Axis.h>
#include <sensors/IGPSSensor.h>
#include <sensors/ISrf02Rangefinder.h>

namespace eLSA {

struct I2cDomainInput_t {
	sensors::ISensor3Axis* accelerometer;
	sensors::ISensor3Axis* gyroscope;
	sensors::ISensor3Axis* magnetometer;
	sensors::IDistanceSensor* ultrasonic[3];
};

struct I2cDomainOutput_t {
	actuators::Motorcontroller* motorcontroller;
};

struct I2cDomainDisplay_t {
	display::DisplaySSD1306* display;
};

struct SPIDomain_t  {
	//ICommunicationLink
};

struct UARTDomain_t {
	sensors::IGPSSensor* gpsSensor;
};

struct eLSAEnvironment_t {
	struct I2cDomainInput_t i2cDomainInput;
	struct I2cDomainOutput_t i2cDomainOutput;
	struct I2cDomainDisplay_t i2cDomainDisplay;
	struct SPIDomain_t spiDomain;
	struct UARTDomain_t uartDomain;
};

class eLSASystem {
public:
	eLSASystem();
	virtual ~eLSASystem();
};

} /* namespace eLSA */

#endif /* ENVIRONMENT_ELSASYSTEM_H_ */
