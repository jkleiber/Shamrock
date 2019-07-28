#include <RobotLib.h>
#include "TrackingLoop.h"

// Encoder Constants
#define LEFT_ENCODER_A 3
#define LEFT_ENCODER_B 12
#define RIGHT_ENCODER_A 2
#define RIGHT_ENCODER_B 11
#define LEFT_ENCODER_CONST (float)(0.006464)
#define RIGHT_ENCODER_CONST (float)(0.006464)

// Motor Constants
#define LEFT_ENABLE     10
#define LEFT_A          5
#define LEFT_B          8
#define RIGHT_ENABLE    9
#define RIGHT_A         7
#define RIGHT_B         6

/************
 * Devices
 ************/
// Encoders
QuadratureEncoder left_encoder; // 2-7/8" wheel, rotated 3 times, encoder output: 4192 -> K = 0.006464
QuadratureEncoder right_encoder;// 2-7/8" wheel, rotated 3 times, encoder output: 4192 -> K = 0.006464


// Motors
Motor left_motor;
Motor right_motor;

// Tracking loops for velocity estimates
TrackingLoop left_tracking;
TrackingLoop right_tracking;

float left_vel, left_accel, right_vel, right_accel;


void tracking_loop()
{
    // Update the tracking loops
    left_tracking.update(left_encoder.getValue());
    //right_tracking.update(right_encoder.getValue());

    left_vel = left_tracking.get_velocity_estimate();
    left_accel = left_tracking.get_accel_estimate();

    // print results to the console
    Serial.print(left_encoder.getValue());
    Serial.print(" ");
    Serial.print(left_vel);
    Serial.print(" ");
    Serial.print(left_accel);
    Serial.println();
}


void position_loop()
{
    Serial.print(left_encoder.getValue());
    Serial.print(" ");
    Serial.print(right_encoder.getValue());
    Serial.println();
}


void left_encoder_isr()
{
    left_encoder.process();
}


void right_encoder_isr()
{
    right_encoder.process();
}


void setup()
{
    // Initialize encoders
    left_encoder.begin(LEFT_ENCODER_A, LEFT_ENCODER_B, LEFT_ENCODER_CONST);
    right_encoder.begin(RIGHT_ENCODER_A, RIGHT_ENCODER_B, RIGHT_ENCODER_CONST);

    // Setup serial output
    Serial.begin(115200);

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_A), &left_encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_A), &right_encoder_isr, CHANGE);

    // Initialize the motors
    left_motor.begin(LEFT_A, LEFT_B, LEFT_ENABLE);
    //right_motor.begin(RIGHT_A, RIGHT_B, RIGHT_ENABLE, true);
}


void loop()
{
    tracking_loop();
    //position_loop();

    left_motor.output(0.5*sin((float)(millis()/1000.0) * 0.45));

    delay(5);
}