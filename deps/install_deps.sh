#!/usr/bin/sh

# TODO: consider using vcs if that seems appropriate

$arduino_path = "~/arduino-1.8.8/libraries"

# Clone RobotLib to the arduino folder
git clone https://github.com/jkleiber/RobotLib.git $arduino_path

# Install rosserial and rosserial arduino
sudo apt-get install -y ros-kinetic-rosserial ros-kinetic-rosserial-arduino

# Remind user to install extra deps
echo "Install the following dependencies from the Arduino Library Manager:"
echo "- Adafruit BNO055 Library"
