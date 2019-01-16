# eLSA - The embedded Land Surveying Automaton

## Introduction

The eLSA platform is a software solution for user specific land surveying applications. The eLSA platform itself provides handling of autonomous driving to waypoints,
hazard detection, malfunction report and communication with an operator. The platform can be used to extend the capability of an eLSA Robot through the given eLSA Layer, while
it still provides access to hardware components.

### Architecture

In this section we want to take a detailed look at the eLSA Layer Architecture, which consists of 5 layers. 

![Image of eLSA Architecture](general/elsa_architecture.png)

#### User Application

This is the user level application. The layer has access to eLSA specific components like the communication link or hazard detection but also to externally defined hardware
components like sensors and actuators. Thus it is possible to extend the eLSA application for custom uses.

#### eLSA Application

The eLSA Application is the functioning layer of the eLSA platform and contains the logic of an eLSA robot. It handles the waypoint management, the movement control while considering
obstacles and hazards and reporting mechanism through the communication link.

#### eLSA HAL

This is the HAL at the eLSA side. The eLSA platform is hardware and platform independent. The reason is because of this layer. The layer defines rules and interfaces, which
must be implemented from the lower layer, so that the eLSA Application can use these implementations.

#### eLSA User HAL

The eLSA User HAL is the user implementation of the eLSA HAL. It just provides an abstraction to the hardware for the eLSA HAL. In this layer, it is possible to use middleware
like RTOS.

#### Hardware

This is the hardware layer with all the possible hardware components for the application and their communication protocols and interfaces.

## Tools

The list represents the used tools within the project.

Name                         | Description
-----------------------------|-----------------------------------------------------------------------------
Visual Paradigm Community    | All-in-one modelling tool, which was used in the project for SysML-Modeling
Pencil Project               | Diagram modelling tool for simple diagrams
Docsify                      | JavaScript application to display markdown written documenmts on GitHub Pages
Doxygen                      | Documentation site generator for C++-Code
Atollic TrueSTUDIO for STM32 | Eclipse based IDE for embedded systems development in use for C++-Coding and debug
STM32CubeMX                  | TrueStudio-Plugin: C code generator and configurator for STM32 microcontroller platform



## Requirement Diagrams

## Block Diagrams

## State Diagrams

## Class Diagrams

## Hardware - eLSA Robot

This section shows the used hardware and their configurations in detail.

### Parts

#### µController-Board

| Description                 | Note | Distributor | Article No.  | Count |
| --------------------------- | ---  | ----------- | ------------ | ----- |
| STM32 Nucleo 64 Basis-Board | µC   | Conrad      | 1416928 - 62 | 1     |

#### Chassis

| Description                | Note    | Distributor | Article No. | Count |
| -------------------------- | --------| ----------- | ----------- | ----- |
| Roboterchassis Arexx RP5/6 | chassis | Conrad      | 191152 - 62 | 1     |

#### Actuators

| Description                         | Note          | Distributor | Article No.   | Interface | Count |
| ----------------------------------- | ------------- | ----------- | ------------- | --------- | ----- |
| Adafruit Motor/Stepper/Servo Shield | motor control | Mouser      | 485 - 1438    | I2C       | 1     |
| Display 128x32 I2C OLED             | display       | Mouser      | 485 - 931     | I2C       | 1     |

#### Sensors

| Description                         | Note                            | Distributor   | Article No. | Interface     | Count |
| ----------------------------------- | ------------------------------- | ------------- | ----------- | ------------- | ----- |
| Adafruit Ultimate GPS Logger Shield | GPS                             | Mouser        | 485 - 1438  | UART          | 1     |
| Adafruit 9-DOF Accel/Mag/Gyro       | acceleration sensing            | Mouser        | 485-3387    | I2C, SPI      | 1     |
| SRF02 I2C Ultraschall-Sensor        | ultrasonic distance measurement | Robotshop.com | RB-Dev-20   | I2C           | 1     |
| Sharp GP2Y0D805Z0F IR-Sensor        | optical distance measurement    | Robotshop.com | RB-Pol-158  | Analog        | 3     |
| DFRobot Moisture Sensor             | humidity                        | Robotshop.com | RB-Dfr-161  | Widerstand    | 1     |

#### Communication

| Description         | Note    | Distributor | Article No. | Interface     | Count |
| ------------------- | ------- | ----------- | ----------- | ------------- | ----- |
| Adafruit LoRa Modul | LoRa    | Mouser      | 485-3072    | SPI           | 1     |

#### Power Supply

| Description                                            | Note            | Distributor | Article No. | Count |
| ------------------------------------------------------ | --------------- | ----------- | ----------- | ----- |
| Conrad energy Modellbau-Akkupack (NiMh) 7.2 V 3000 mAh | motor batteries | Conrad      | 206028 - 62 | 1     |

#### Miscellaneous

| Description                          | Note                              | Distributor | Article No. | Count |
| ------------------------------------ | --------------------------------- | ----------- | ----------- | ----- |
| GPS Antenna                          | to be determined                  |             |             |       |
| Casing                               | to be determined                  |             |             |       |

### Domains

The hardware is split into 5 domains, while the microcontroller holds a special place as the central hardware component.
It shows the logical relations and their interfaces to the microcontroller. It helps to have an overview of all the used
components in general.

![eLSA Hardware Peripherals](hardware/peripherals/elsa_peripherals.png)

Domain                 | Function
-----------------------|-----------
I2C Domain 1 (Input)   | simple I2C devices, simple inputs
I2C Domain 2 (Output)  | simple I2C devices, simple outputs
I2C Domain 3 (Display) | i2c devices for display specific output
SPI Domain             | spi devices with more complex functions (e.g. protocols)
UART Domain            | uart devices with more complex functions (e.g. protocols)

### Configuration

The configuration of the microcontroller was done with the STM32CubeMX plugin, which generated this document.

```pdf
	hardware/mcuBoard/eLSA_RobotHwConfig.pdf
```