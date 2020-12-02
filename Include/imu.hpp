//Parent Class for IMU

/*
Copied from aero-cpp-lib/include/sensors.hpp and aero-cpp-lib/include/data.hpp
*/

#pragma once

#if defined(ARDUINO) || defined(CORE_TEENSY)
    #include "Arduino.h"
#else
    #include <cstddef>
    #include <cstdint>
#endif

//#include "Data.hpp"           //No longer include this?

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup sensor          //Change sensor to IMU?
 *  @{
 */

//! Sensor interfaces
namespace sensor                //Change sensor to IMU?
{
  
/**
* @brief Raw IMU data
*/
struct __attribute__((__packed__)) IMU_t          //From aero-cpp-lib/include/Data.hpp
{                                                 //Can this just be added to the class now? How do we need to access stuff?
    int16_t ax;                                   //For the stuff from Data, should it be put somewhere else or make it specific to the IMU?
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t mx;
    int16_t my;
    int16_t mz;
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
};
    
/**
* @brief Enum class for data signatures of each struct that can be sent
*/   
//enum class Signature{ Pitot, IMU, GPS, Enviro, Batt, Config, Status, Actuators, AData, Cmds, Drop };               //Since now its only an IMU, dont need the rest here?

/**
 * @brief Abstract IMU definition
 */
class IMU
{
public: 

    /** @brief Defines configuration data for the IMU */
    struct Config_t
    {
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the IMU
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the IMU with user configuration
     * 
     * @param config user selected IMU configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( IMU::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the IMU data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get imu data
     * 
     * @return const def::IMU_t& reference to IMU's data struct
     */
    const def::IMU_t& data(void) { return m_data; }                                 //Struct with data is now in this class, so this might need to change?

    /**
     * @brief Destructor
     */
    virtual ~IMU(){}

protected:
    // Hidden constructor that only children can redefine
    IMU(){}

    // Member variables
    def::IMU_t m_data;      // For imu data
    IMU::Config_t m_config; // For imu configuration
};
  
} //End of namespace sensor
  
} //End of namespace aero
