#include "TrackingLoop.h"


TrackingLoop::TrackingLoop()
{
    // initialize the PI controller
    this->kp = 40.0;
    this->ki = 900.0;
    this->loop_pid.initialize(0, this->kp, this->ki, 0);
    
    // Unbounded output required on the PID
    this->loop_pid.set_bounded(false);

    // initialize the estimator
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;
}


TrackingLoop::TrackingLoop(float kp, float ki)
{
    // initialize the PI controller
    this->kp = kp;
    this->ki = ki;
    this->loop_pid.initialize(0, this->kp, this->ki, 0);

    // Unbounded output required on the PID
    this->loop_pid.set_bounded(false);

    // initialize the estimator
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;
}


void TrackingLoop::operator=(const TrackingLoop& quad_encoder)
{
    // copy values from one object to another
    this->loop_pid = quad_encoder.loop_pid;
    this->kp = quad_encoder.kp;
    this->ki = quad_encoder.ki;
    this->last_time = quad_encoder.last_time;
    this->pos_estimate = quad_encoder.pos_estimate;
    this->vel_estimate = quad_encoder.vel_estimate;
}


void TrackingLoop::reset()
{
    // set estimates to 0
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;

    // Reset the PID
    this->loop_pid.initialize(0, this->kp, this->ki, 0);

    // reset the time tracking
    this->last_time = millis();
}


void TrackingLoop::update(float measurement)
{
    // Declare local vars
    float dt;
    float pos_error;
    float integrator;

    // Get the elapsed time (sec)
    dt = (millis() - this->last_time) / 1000.0;
    
    // Estimate the position from the velocity estimates
    this->pos_estimate += this->vel_estimate * dt;

    // Calculate error
    pos_error = measurement - this->pos_estimate;

    // Integrate error
    integrator = this->ki * pos_error * dt;

    // Get PI output
    this->vel_estimate = integrator + (pos_error * this->kp);

    Serial.print(this->pos_estimate);
    Serial.print("\t");
    Serial.print(measurement);
    Serial.print("\t");
    Serial.print(pos_error);
    Serial.print("\t");
    Serial.print(integrator);
    Serial.print("\t");
//
    //// Get new velocity estimate from PID controller by comparing position estimate to actual position
    //this->vel_estimate = this->loop_pid.getOutput(measurement, this->pos_estimate);
    ////this->vel_estimate = this->loop_pid.get_integrator_value();
//
    Serial.println(this->vel_estimate);

    // Set the last time to now
    this->last_time = millis();
}


float TrackingLoop::get_velocity_estimate()
{
    return this->vel_estimate;
}