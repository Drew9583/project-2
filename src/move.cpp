#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/BumperEvent.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "project-1/teleop.h"

ros::Publisher cmd_vel_pub;
geometry_msgs::Twist cmd_vel_msg;
bool bumperHit = false;

void haltRobot()
{
    cmd_vel_msg.linear.x = 0.0; //set linear velocity to 0
    cmd_vel_msg.angular.z = 0.0; //set angular velocity to 0
    cmd_vel_pub.publish(cmd_vel_msg);
    ROS_INFO("Robot has been halted!");
}

void moveForward()
{
    cmd_vel_msg.linear.x = 0.2; //drive forward at a rate of 0.2
}

void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
    if (msg->state == kobuki_msgs::BumperEvent::PRESSED)
    {
        ROS_INFO("Bumper pressed!");
        bumperHit = true;  // Set the bumperHit flag to true
        haltRobot();
    }

}

int main(int argc, char **argv)
{   
    ros::init(argc, argv, "robot_control_node");
    ros::NodeHandle nh;
    
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Subscriber bumper_sub = nh.subscribe("/mobile_base/events/bumper", 1, bumperCallback);

    ros::Rate loop_rate(10); // controls the frequency that the loop executes (in Hertz)

    ROS_INFO("I did something");

    getControl object;
    //object.control();

    while (ros::ok())
    {
	ROS_INFO("My boolean value is %s", object.getdoMove() ? "true" : "false");
	moveForward();
	cmd_vel_pub.publish(cmd_vel_msg);
	ros::spinOnce(); // processes pending ROS messages and/or callbacks
        loop_rate.sleep();
    }
}
