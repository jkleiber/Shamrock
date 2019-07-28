#ifndef TRACKING_LOOP_H
#define TRACKING_LOOP_H

#include <Arduino.h>
#include <PIDController.h>

class TrackingLoop
{
    public:
        // Constructor
        TrackingLoop();
        TrackingLoop(float kp, float ki);

        // Copy-assign
        void operator=(const TrackingLoop& tracker);

        // Modifiers
        void reset();

        // Accessors
        float get_velocity_estimate();
        float get_accel_estimate();
        float update(float measurement);

    private:
        // Estimation variables
        volatile float accel_estimate;
        volatile float vel_estimate;
        volatile float pos_estimate;

        // PI controller
        PIDController loop_pid; //accel_pid, 
        float kp;
        float ki;

        // Time tracking
        float last_time;
};

#endif