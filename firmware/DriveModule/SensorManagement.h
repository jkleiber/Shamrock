#ifndef SENSOR_MANAGEMENT_H
#define SENSOR_MANAGEMENT_H

// ROS Includes
#include <ros.h>
#include <shamrock_msgs/SensorData.h>

// Shamrock sensors
#include "Devices.h"
#include "DriveModuleConstants.h"

// Send sensor data back to the raspberry pi
shamrock_msgs::SensorData sensor_data;
ros::Publisher sensor_data_pub("shamrock_drive/sensors", &sensor_data);


void sensor_update()
{
    // Update tracking loops
    left_tracking.update(left_encoder.getValue());
    right_tracking.update(right_encoder.getValue());

    // Update velocity
    sensor_data.velocity = (left_tracking.getVelocityEstimate() + right_tracking.getVelocityEstimate()) / 2.0;
}


#endif