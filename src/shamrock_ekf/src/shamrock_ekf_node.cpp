#include <ros/ros.h>

// Message Types
#include <shamrock_msgs/State.h>
#include <sensor_msgs/Imu.h>

// Publishers
ros::Publisher state_pub;

// Subscribers
ros::Subscriber imu_sub;
ros::Subscriber vel_sub;

// Timers
ros::Timer recalc_timer;


//
// Callbacks
//

void imu_callback(sensor_msgs::Imu::ConstPtr& imu_msg)
{
    // TODO: receive IMU data
}


void vel_callback()
{
    // TODO: receive wheel velocity data
}


void recalculate_state(ros::TimerEvent time_event)
{
    // TODO: calculate the robot state using the EKF calculations
}


int main(int argc, char** argv)
{
    // Initialize the EKF node with a name
    ros::init(argc, argv, "shamrock_ekf_node");

    // Set up a node handle
    ros::NodeHandle ekf_node;

    // Publishers
    state_pub = ekf_node.advertise<shamrock_msgs::State>(ekf_node.resolveName("shamrock/ekf/state"), 1);

    // Subscribers
    imu_sub = ekf_node.subscribe(ekf_node.resolveName("/imu"), 1, &imu_callback);

    // Timers
    recalc_timer = ekf_node.createTimer(ros::Duration(0.05), &recalculate_state);

    // Pump callbacks
    ros::spin();

    return 0;
}