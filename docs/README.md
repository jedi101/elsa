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

## Requirement Diagrams

## Block Diagrams

## State Diagrams

## Class Diagrams
