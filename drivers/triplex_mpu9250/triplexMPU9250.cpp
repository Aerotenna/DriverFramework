#include <stdint.h>
#include <string.h>
#include "math.h"
#include "DriverFramework.hpp"
#include "triplexMPU9250.hpp"


#define MPUREG_WHOAMI			0x75

using namespace DriverFramework;

int triplexMPU9250::start()
{
	// Open the device path specified in the class initialization. 
	// attempt to open device in start()
#if defined (__IMU_USE_I2C)
	int result = I2CDevObj::start();


	if (result < 0) {
		DF_LOG_ERR("DevObj start failed");
		DF_LOG_ERR("Unable to open the device path: %s", m_dev_path);
		return result;
	} else {
		DF_LOG_ERR("opened I2C device at %s", m_dev_path);
	}

	result = _setSlaveConfig(MPU9250_SLAVE_ADDRESS,
				 MPU9250_BUS_FREQUENCY_IN_KHZ,
				 MPU9250_TRANSFER_TIMEOUT_IN_USECS);

	if (result < 0) {
		DF_LOG_ERR("Could not set slave config");
	} else {
		DF_LOG_ERR("slave config set");
	}

	// Try to talk to the sensor. 
	uint8_t sensor_id;
	result = _readReg(MPUREG_WHOAMI, &sensor_id, 1);

	if (result < 0) {
		DF_LOG_ERR("Unable to communicate with the sensor");
		return -1;
	} else {
		DF_LOG_ERR("did an I2C read");
	}

	if (sensor_id != MPU_WHOAMI_9250) {
	//if(sensor_id != 0x73) { 
		DF_LOG_ERR("MPU9250 sensor WHOAMI wrong: 0x%X, should be: 0x%X",
			   sensor_id, MPU_WHOAMI_9250);
		result = -1;
		goto exit;
	} else {
		DF_LOG_ERR("sensor id correct");
	}

	//result = mpu6050_init();
/*
	if (result != 0) {
		DF_LOG_ERR("error: IMU sensor initialization failed, sensor read thread not started");
		goto exit;
	} else {
		DF_LOG_ERR("I2C IMU initialized");
*/
	
#else
	int result = SPIDevObj::start();

	if (result != 0) {
		DF_LOG_ERR("DevObj start failed");
		DF_LOG_ERR("Unable to open the device path: %s", m_dev_path);
		return result;
	} else {
		DF_LOG_ERR("opened device at %s", m_dev_path);
	}

	/* Set the bus frequency for register get/set. */
	result = _setBusFrequency(SPI_FREQUENCY_1MHZ);

	if (result != 0) {
		DF_LOG_ERR("failed setting SPI bus frequency: %d", result);
	} else {
		DF_LOG_ERR("SPI frequency set");
	}

	/* Try to talk to the sensor. */
	uint8_t sensor_id;
	result = _readReg(MPUREG_WHOAMI, sensor_id);

	if (result != 0) {
		DF_LOG_ERR("Unable to communicate with the MPU9250 sensor");
		goto exit;
	} else {
		DF_LOG_ERR("did an SPI readReg");
	}

#endif

result = DevObj::start();

	if (result != 0) {
		DF_LOG_ERR("DevObj start failed");
		return result;
	}

exit:
	return 0;//result;
}

void triplexMPU9250::_measure()
{

	return;
}
