/**
 * @file IMUTest.ino
 * @author Justin Kleiber (jkleiber8@gmail.com)
 * @brief Test the BNO055 IMU. This file is very similar to 
 *        the raw data example in Adafruit's library.
 * @version 0.1
 * @date 2019-08-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Create an IMU object at the default address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

// IMU variables
uint8_t sys = 0, gyro = 0, accel = 0, mag = 0;

void setup()
{
    Serial.begin(115200);

    // Make sure the IMU is connected
    if(!bno.begin())
    {
        Serial.println("ERROR: IMU not connected correctly");
        while(1){}
    }

    // Setup bno settings
    bno.setExtCrystalUse(true);
}

void loop()
{
    bno.getCalibration(&sys, &gyro, &accel, &mag);

    // Print cal status
    Serial.print("CAL -- ");
    Serial.print("System: ");
    Serial.print(sys);
    Serial.print(" Gyro: ");
    Serial.print(gyro);
    Serial.print(" Accel: ");
    Serial.print(accel);
    Serial.print(" Mag: ");
    Serial.print(mag);


    Serial.println();
}