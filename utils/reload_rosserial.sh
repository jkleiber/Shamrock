#!/bin/bash

# In order to reload the rosserial libraries folder automatically
# run this script
arduino_path="${HOME}/Arduino/libraries/"
ros_lib_path="${arduino_path}/ros_lib"
echo "ros_lib folder: "  $ros_lib_path

# Remove the ros_lib folder from the arduino libraries directory
rm -rf $ros_lib_path

# Regenerate the ros_lib folder
rosrun rosserial_arduino make_libraries.py $arduino_path
