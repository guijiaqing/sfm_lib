#include "CommunicateInterface.h"

CommunicateInterface::CommunicateInterface(ros::NodeHandle &nh,Robot *robot):nh_(nh),robot_(robot)
{
  std::cout<<"enter"<<std::endl;
  target_pose_list_srv_ = nh.advertiseService("send_targetPoints", &CommunicateInterface::deal_GetNavTargets, this);
  display_signal_sub_ = nh_.subscribe<sfm_lib::DisplayInput>("display_input", 1, &CommunicateInterface::DisplaySignalCb, this);
}

CommunicateInterface::~CommunicateInterface()
{
}

bool CommunicateInterface::deal_GetNavTargets(sfm_lib::targets_list::Request  &req,
  sfm_lib::targets_list::Response &res){
  ROS_INFO("Enter server");
  robot_->task_date_v_ = req;
  robot_->changeTask(TaskInput::ADD_TASK);
}

void CommunicateInterface::DisplaySignalCb(const sfm_lib::DisplayInputConstPtr &signal){
  ROS_INFO("收到任务:%d",signal->signal);
  robot_->changeTask((TaskInput)(signal->signal));
}
