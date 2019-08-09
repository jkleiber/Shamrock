/**
 * @file DriveModule.ino
 * @author Justin Kleiber (jkleiber8@gmail.com)
 * @brief Controlling Shamrock's drive train and providing 
 *        data to the main board
 * @version 0.1
 * @date 2019-08-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

// ROS Includes
#include <ros.h>

// RobotLib
#include <RobotLib.h>

// Shamrock Drive Module Code
#include "Devices.h"
#include "DriveControl.h"
#include "DriveModuleConstants.h"
#include "SensorManagement.h"


// Create the drive node
ros::NodeHandle_<ArduinoHardware, 1, 1, 80, 80> drive_node;


// Track control loop timing
unsigned long last_loop_time;


/**
 * @brief Set up the program
 * 
 */
void setup()
{
    // Initialize the ROS node and advertise publishers
    drive_node.initNode();
    drive_node.advertise(sensor_data_pub);

    // Initialize the devices
    device_init();

    // Start loop timing
    last_loop_time = millis();
}


/**
 * @brief Main program loop
 * 
 */
void loop()
{
    // Update sensor data
    sensor_update();

    // Pump callbacks
    drive_node.spinOnce();

    // Control drivetrain
    drive_control();

    // Wait for loop update time to elapse
    while((millis() - last_loop_time) * MILLIS_PER_SECOND < LOOP_PERIOD){}

    // Update timing tracker
    last_loop_time = millis();
}