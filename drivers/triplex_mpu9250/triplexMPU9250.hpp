//#define __IMU_USE_I2C //need to not use this probably
#include "ImuSensor.hpp"

//#define DRV_DF_DEVTYPE_MPU6050 0x45

#define MPU_WHOAMI_9250		 0x73
#define MPU9250_SLAVE_ADDRESS 0x68       /* 7-bit slave address */

// update frequency 1000 Hz
#define MPU9250_MEASURE_INTERVAL_US 2000

#define MPU9250_BUS_FREQUENCY_IN_KHZ 400
#define MPU9250_TRANSFER_TIMEOUT_IN_USECS 900

namespace DriverFramework
{

//#define MPU9250_MEASURE_INTERVAL_US 4000 //in us, 1000 is a 1kHz

class triplexMPU9250: public ImuSensor
{
public:
	triplexMPU9250(const char *device_path,bool mag_enabled) :
		ImuSensor(device_path, MPU9250_MEASURE_INTERVAL_US, true) // false = sensor has no mag
	{
	}
	virtual int start();

protected:
	virtual void _measure();

};

}
// namespace DriverFramework

