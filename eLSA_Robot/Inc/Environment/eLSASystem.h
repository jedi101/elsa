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

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct describes/contains all sensors in the i2c input domain used in an eLSA robot
 */
struct I2cDomainInput_t {
	sensors::ISensor3Axis* accelerometer; ///< handle to an accelerometer used used in hazard detection
	sensors::ISensor3Axis* gyroscope; ///< handle to a gyroscope used in hazard detection
	sensors::ISensor3Axis* magnetometer; ///< handle to magnetometer which is necessary as a compass (heading)
	sensors::IDistanceSensor* ultrasonic[3]; ///< handle to ultrasonic distance sensors used in pathfinding and hazard detection
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct describes/contains all actuators in the i2c output domain used in an eLSA robot
 */
struct I2cDomainOutput_t {
	actuators::Motorcontroller* motorcontroller; ///< handle to motorcontroller
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct describes/contains the display in the i2c display domain used in an eLSA robot
 */
struct I2cDomainDisplay_t {
	display::DisplaySSD1306* display; ///< handle to display
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct describes/contains the operator communication link in the spi communication domain used in an eLSA robot
 */
struct SPIDomain_t  {
	//ICommunicationLink ///< handle to commmunication link
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct describes/contains the gps sensor in the UART domain used in an eLSA robot
 */
struct UARTDomain_t {
	sensors::IGPSSensor* gpsSensor; ///< handle to GPS sensor
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This struct is used to set the environment for the eLSA system including interface handles
 * 			and configuration parameters.
 * 			eLSA divides the competences of input, output as well as interface hardware technology into domains.
 * 			The collection of these domains are called "environment"
 */
struct eLSAEnvironment_t {
	struct I2cDomainInput_t i2cDomainInput; ///< Competence: input/sensors, Technology: I2C
	struct I2cDomainOutput_t i2cDomainOutput; ///< Competence: output/actuators, Technology: I2C
	struct I2cDomainDisplay_t i2cDomainDisplay; ///< Competence: (special) output/display, Technology: I2C
	struct SPIDomain_t spiDomain; ///< Competence: bidirectional communication, Technology: SPI
	struct UARTDomain_t uartDomain; ///< Competence: input(solely GPS), Technology: UART
};

/**
 * @author	Tobias Koppmann
 * @date	16.01.2019
 * @brief	This class encapsulates the eLSA system containing all essential blocks
 * 			- condition monitoring
 * 			- hazard detection
 * 			- signaler (optical, visual)
 * 			- communcation link to operator
 * 			- motion planning (processing of the GPS-point queue and pathfinding)
 * 			- environment surveillance (object detection etc.)
 * 			- gps position sensing
 * 			- motor controller
 */
class System {
public:
	/**
	 * @brief The constructor takes the environmental variables and creates necessary objects
	 * @param env Pointer The eLSA environmental conditions and configuration
	 */
	 System(struct eLSAEnvironment_t env);

	virtual ~ System();

	/**
	 * @brief This method reintializes the eLSASystem (states, initial values, logs, etc.)
	 */
	void reset(void);

	/**
	 * @brief This method runs the whole eLSASystem
	 */
	void run(void);
};

} /* namespace eLSA */

#endif /* ENVIRONMENT_ELSASYSTEM_H_ */
