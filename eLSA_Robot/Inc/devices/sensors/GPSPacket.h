/*
 * GPSPacket.h
 *
 *  Created on: 04.12.2018
 *      Author: Richard
 */

#ifndef GPSPACKET_H_
#define GPSPACKET_H_

namespace eLSA {
namespace sensors {

class GPSPacket {
	public:
		GPSPacket(float longitude, float latitude);
		float getLongitude();
		float getLatitude();

	private:
		float longitude;
		float latitude;
};

}//namespace sensors
}//namespace eLSA

#endif /* GPSPACKET_H_ */
