#ifndef SENSOR_MANAGEMENT_H
#define SENSOR_MANAGEMENT_H


// Shamrock sensors
#include "Devices.h"
#include "DriveModuleConstants.h"


void sensor_update()
{
    // Update tracking loops
    left_tracking.update(left_encoder.getValue());
    right_tracking.update(right_encoder.getValue());

    // Update velocity
    sensor_data.velocity = (left_tracking.getVelocityEstimate() + right_tracking.getVelocityEstimate()) / 2.0;
}


#endif