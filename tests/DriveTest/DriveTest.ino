#include <RobotLib.h>

#define LEFT_ENABLE     10
#define LEFT_A          5
#define LEFT_B          8
#define RIGHT_ENABLE    9
#define RIGHT_A         7
#define RIGHT_B         6

/************
 * Devices
 ************/
// Motors
Motor left_motor;
Motor right_motor;

void setup()
{
    // Initialize the motors
    left_motor.begin(LEFT_A, LEFT_B, LEFT_ENABLE, true);
    right_motor.begin(RIGHT_A, RIGHT_B, RIGHT_ENABLE, true);

    // Drive straight
    left_motor.output(0.3);
    right_motor.output(0.3);
}

void loop()
{
    delay(20);
}