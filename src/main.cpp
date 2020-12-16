#include <ros/ros.h>
#include "Robot.h"


int main(int argc,char** argv){
  ros::init(argc,argv,"fsm_test");
  ros::NodeHandle n;
  ROS_INFO("robot init begin");
  Robot robot_(n);
  //ROS_INFO("new robot");
  ros::spin();
}
