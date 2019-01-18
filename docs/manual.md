# eLSA - Manual

## Getting started

The code below is all you need for running the eLSA program, considering all eLSA characteristics are
fulfilled. You can think about the code below as a general template. For more information about the function
of the eLSA platform refer to the project and code documentation!


```cpp
#include "Environment/eLSASystem.h"

int main() {

	eLSAEnvironment_t env;
	
	/**********************************************************
	* INSTANTIATE IMPLEMENTATIONS OF THE ELSA INTERFACES HERE *
	***********************************************************/
	
	//Initialize the eLSA environment with the implemented interfaces
	I2CDomainInput_t in;
	in.accelerometer = /* POINTER TO eLSA::sensors::ISensor3Axis object */
	in.gyroscope = /* POINTER TO eLSA::sensors::ISensor3Axis object */
	in.magnetometer = /* POINTER TO eLSA::sensors::ISensor3Axis object */
	in.ultrasonic[0] = /* POINTER TO eLSA::sensors::IDistanceSensor object (LEFT DISTANCE SENSOR) */
	in.ultrasonic[1] = /* POINTER TO eLSA::sensors::IDistanceSensor object (MIDDLE DISTANCE SENSOR) */
	in.ultrasonic[2] = /* POINTER TO eLSA::sensors::IDistanceSensor object (RIGHT DISTANCE SENSOR) */
	env.i2cDomainInput = in;
	
	I2CDomainOutput_t out;
	out.motorcontroller = /* POINTER TO eLSA::actuators::Motorcontroller object */
	env.i2cDomainOutput = out;
	
	I2CDomainDisplay_t display;
	display.display = /* POINTER TO eLSA::display::DisplaySSD1306 object */
	env.i2cDomainDisplay = display;
	
	SPIDomain_t spi;
	spi.link = /* POINTER TO eLSA::ICommunicationLink object */
	env.spiDomain = spi;
	
	SPIDomain_t uart;
	uart.gpsSensor = /* POINTER TO eLSA::sensors::IGPSSensor object */
	env.uartDomain = uart;
	
	eLSA::System eLSASystem(env);
	eLSASystem.run();
}
```