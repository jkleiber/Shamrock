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
        void operator=(const TrackingLoop& quad_encoder);

        // Modifiers
        void reset();
        void update(float measurement);

        // Accessors
        float get_velocity_estimate();

    private:
        // Estimation variables
        float vel_estimate;
        float pos_estimate;

        // PI controller
        PIDController loop_pid;
        float kp;
        float ki;

        // Time tracking
        float last_time;
};

#endif