# eLSA Peripherals Bus Domain And Address Tables

The following tables are describing the bus domains and address usage for the multiple peripherals used on eLSA.
Since the standard hardware implementation uses a STM32 Nucleo-F411RE Board the given interfaces are specific to this board respectively the STM32F411RETx MCU.
The same applies to the bus addresses which are specific to the used devices.

The interface names are provided in the brackets after the domain names.



##I2C

###Sensor Domain (I2C1)

| Peripheral / Functionality | Device                                                    | AddressBYTE (Read/Write) |
| -------------------------- | :-------------------------------------------------------- | :----------------------: |
| Accelerometer              | Analog Devices ADXL345 (on Sparkfun 9DoF Stick SEN-10724) |        0x3A/0x3B         |
| Magnetometer (Compass)     | Honeywell HMC5883L (on Sparkfun 9DoF Stick SEN-10724)     |        0x3D/0x3C         |
| Gyroscope                  | InvenSense ITG-3200 (on Sparkfun 9DoF Stick SEN-10724)    |        0xD0/0xD1         |
| supersonic distance 1      | Robot Electronics SRF02                                   |        0xE0/0xE1         |
| supersonic distance 2      | Robot Electronics SRF02                                   |        0xE2/0xE3         |
| supersonic distance 3      | Robot Electronics SRF02                                   |        0xE4/0xE5         |

###Actuator Domain (I2C2)

| Peripheral / Functionality | Device                    | AddressBYTE (Read/Write) |
| -------------------------- | ------------------------- | :----------------------: |
| Motordrivers               | Adafruit Motorshield v2.3 |        0x60/0x61         |

###Display / UI Domain (I2C3)

| Peripheral / Functionality | Device                   | AddressBYTE (Read/Write) |
| -------------------------- | ------------------------ | :----------------------: |
| Display                    | Adafruit 128x32 I2C OLED |        0x78/0x79         |



## SPI (SPI2)

| Peripheral / Functionality | Device                       |                Address                 |
| -------------------------- | ---------------------------- | :------------------------------------: |
| LoRa Communication         | Dragino LoRa/GPS Shield v1.3 | [p2p connection - no slave select pin] |

## UART (USART6)

| Peripheral / Functionality | Device                       |     Address      |
| -------------------------- | ---------------------------- | :--------------: |
| GPS                        | Dragino LoRa/GPS Shield v1.3 | [p2p connection] |

