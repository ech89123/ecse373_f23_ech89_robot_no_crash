#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/Twist.h"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

ros::Publisher *p_vel;
sensor_msgs::LaserScan msg;
bool hitWall = false;
double wall_dist = 0.0;

void desCallback(const geometry_msgs::Twist::ConstPtr& des_msg)
{

  geometry_msgs::Twist vel_msg;

  vel_msg = *des_msg;

  if (hitWall && (vel_msg.linear.x > 0.0))
  {
    vel_msg.linear.x = 0.0;
    ROS_INFO_THROTTLE(0.5,"Stop");
  }
  else if (vel_msg.linear.x < 0.0) 
  {
    hitWall = false;
  }

  p_vel->publish(vel_msg);
  
}

void lidarCallback (const sensor_msgs::LaserScan msg)
{
  hitWall = false;
  for (int index = 45; index < 225; index++) 
  {
    if (msg.ranges[index] < wall_dist)
    {
      hitWall = true;
      break;
    }
  }

}

int main(int argc, char **argv)
{
  ROS_INFO("Starting up the Node!!");
  
  ros::init(argc, argv, "robot_no_crash_node");

  ros::NodeHandle n;

  ros::Publisher cmd_vel = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  p_vel = &cmd_vel;

  ros::Subscriber des_vel = n.subscribe("des_vel", 10, desCallback);
  ros::Subscriber lidar_op = n.subscribe("laser_0", 10, lidarCallback);

  ros::Rate loop_rate(10);



  ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);

  int count = 0;
  
  while (ros::ok())
  {

    geometry_msgs::Twist des_msg;
    cmd_vel.publish(des_msg);

  if (n.getParamCached("wall_dist", wall_dist))
  {
    ROS_INFO("wall_dist is now: [%2.2f]", wall_dist);
  }

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}


