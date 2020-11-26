/*
 * From onboard-software-2018-19/src/Onboard Software V1.0/main/IMU.h
 * and onboard-software-2018-19/src/Onboard Software V1.0/main/IMU_MPU6050.h
 */

#ifndef IMU_MPU6050_h
#define IMU_MPU6050_h

/*
 * File Purpose
 *    Mostly for reference now?
 *    Interface for the IMU sensor
 *    and class that implements it for the MPU6050
 */

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class IMU_ONBOARD_2018/19 {
  public: 
    IMU_ONBOARD_2018/19();
    ~IMU_ONBOARD_2018/19();
    virtual float getYaw() = 0;
    virtual float getPitch() = 0;
    virtual float getRoll() = 0;
    virtual void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg) = 0;
    virtual void update() = 0;
    virtual void printYPR() = 0;

};

class IMU_MPU6050 : public IMU_ONBOARD_2018/19{                                     //This class implements the above interface rather than the one from aero-cpp-lib
  public: 
    IMU_MPU6050();
    ~IMU_MPU6050();

    // gets sensor data
    float getYaw();
    float getPitch();
    float getRoll();

    // init with offsets
    void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg);

    // update sensor
    void update();

    // print for debugging
    void printYPR();
};

#endif
