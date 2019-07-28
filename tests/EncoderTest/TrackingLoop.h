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
        void update(float measurement);

        // Accessors
        float get_velocity_estimate();
        float get_accel_estimate();

    private:
        // Estimation variables
        float accel_estimate;
        float vel_estimate;
        float pos_estimate;

        // PI controller
        PIDController vel_pid, accel_pid;
        float kp;
        float ki;

        // Time tracking
        unsigned long last_time;
};

#endif