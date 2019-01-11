#ifndef DEVICES_SENSORS_IDISTANCESENSOR_H_
#define DEVICES_SENSORS_IDISTANCESENSOR_H_

namespace eLSA {
namespace sensors {

class IDistanceSensor {
    public:
        unsigned int getDistanceInCentimeters(void) = 0;
        unsigned int getDistanceInInches(void) = 0;
        uint8_t isDistanceLowerInCentimeters(unsigned int threshold) = 0;
        uint8_t isDIstanceLowerInInches(unsigned int threshold) = 0;

};

} // namespace sensors
} // namespace eLSA
#endif /* DEVICES_SENSORS_IDISTANCESENSOR_H_ */
