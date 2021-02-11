/** \file AERO_ICM20948.hpp
   @brief All code relating to the IMU sensor
*/

#pragma once

// Include for sensor interfaces; imu needed
#include "src/ICM20948/Teensy-ICM-20948.h"

/**
   @brief Class for a IMU sensor made by SparkFun
   @details It is an I2C sensor with an accelerometer, magnetometer and gyroscope
*/
class AERO_ICM20948 {
  public:

    /**
       @brief Construct a new IMU sensor object
    */
    AERO_ICM20948() {};

    /**
       @brief Initialize sensor object

       @return true If init succeeded
       @return false If init failed
    */
    bool init(TwoWire &wirePort) {
      icm20948.init(icmSettings, wirePort);
      m_initialized = true;
      return m_initialized;
    }

    /**
       @brief Update sensor value by reading registers over I2C

       @return true sensor value updated
       @return false sensor value not updated
    */
    bool update(float *accel, float *gyro, float *quat) {
      // If system is not initialized, return error
      if (!m_initialized) {
        return false;
      }

      icm20948.task();

      if (icm20948.gyroDataIsReady())
      {
        icm20948.readGyroData(&gyro[0], &gyro[1], &gyro[2]);
      }

      if (icm20948.accelDataIsReady())
      {
        icm20948.readAccelData(&accel[0], &accel[1], &accel[2]);
      }

      if (icm20948.quatDataIsReady())
      {
        icm20948.readQuatData(&quat[0], &quat[2], &quat[1], &quat[3]);
        quat[3] *= -1.f;
      }

      return true;
    }

  private:
    bool m_initialized = false;

    TeensyICM20948 icm20948;

    TeensyICM20948Settings icmSettings =
    {
      .mode = 1,                     // 0 = low power mode, 1 = high performance mode
      .enable_gyroscope = true,      // Enables gyroscope output
      .enable_accelerometer = true,  // Enables accelerometer output
      .enable_magnetometer = true,   // Enables magnetometer output
      .enable_quaternion = true,     // Enables quaternion output
      .gyroscope_frequency = 200,      // Max frequency = 225, min frequency = 1
      .accelerometer_frequency = 200,  // Max frequency = 225, min frequency = 1
      .magnetometer_frequency = 70,   // Max frequency = 70, min frequency = 1
      .quaternion_frequency = 200     // Max frequency = 225, min frequency = 50
    };
};
