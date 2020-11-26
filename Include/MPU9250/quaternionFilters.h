//Copied from embedded-software/western-aero-2019-2020/src/MPU9250/quaternionFilters.h

#ifndef _QUATERNIONFILTERS_H_
#define _QUATERNIONFILTERS_H_

#include <Arduino.h>

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                              float gz, float mx, float my, float mz,
                              float deltat);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                            float gz, float mx, float my, float mz,
                            float deltat);
const float * getQ();

#endif // _QUATERNIONFILTERS_H_
