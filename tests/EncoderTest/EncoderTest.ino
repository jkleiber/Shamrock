#include <RobotLib.h>
#include "TrackingLoop.h"

#define LEFT_ENCODER_A 3
#define LEFT_ENCODER_B 12
#define RIGHT_ENCODER_A 2
#define RIGHT_ENCODER_B 11
#define LEFT_ENCODER_CONST (float)(0.006464)
#define RIGHT_ENCODER_CONST (float)(0.006464)

/************
 * Devices
 ************/
// Encoders
QuadratureEncoder left_encoder; // 2-7/8" wheel, rotated 3 times, encoder output: 4192 -> K = 0.006464
QuadratureEncoder right_encoder;// 2-7/8" wheel, rotated 3 times, encoder output: 4192 -> K = 0.006464


// Tracking loops for velocity estimates
TrackingLoop left_tracking;
TrackingLoop right_tracking;


void tracking_loop()
{
    // Update the tracking loops
    left_tracking.update(left_encoder.getValue());
    //right_tracking.update(right_encoder.getValue());

    // print results to the console
    /*
    Serial.print(left_tracking.get_velocity_estimate());
    Serial.print(" ");
    Serial.print(right_tracking.get_velocity_estimate());
    Serial.println();*/
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
}


void loop()
{
    tracking_loop();
    //position_loop();

    delay(5);
}