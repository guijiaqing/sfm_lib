#include "NavState.h"
NavigationState::NavigationState():donavc_("move_base", true)
{
   //donavc_ = new DoNavClient("move_base", true);
}
NavigationState::~NavigationState(){

}
///父导航状态
void NavigationState::enter(TaskState *task)
{
  std::cout<<"enter nav"<<std::endl;
}
NavigationState *NavigationState::handleInput(TaskState *task, NavInput input)
{
    //return new FreeNavState();
}

///目标状态

TargetNavState::TargetNavState(){
  
}
TargetNavState::~TargetNavState(){
  
}
void TargetNavState::enter(TaskState *task)
{
  std::cout<<"enter tar nav"<<std::endl;
  move_base_sendgoal(task);
}
NavigationState *TargetNavState::handleInput(TaskState *task, NavInput input)
{
  switch (input)
  {
  case FREETAR://无目标状态
      ROS_INFO("return free nav state");
      return new FreeNavState();
  case PAUSE://暂停状态
      ROS_INFO("return pause nav state");
      return new PauseNavState();
  default:
    return NULL;
  }
}
void TargetNavState::move_base_sendgoal(TaskState *task){//发送导
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";
 //Set the time stamp to "now"
  goal.target_pose.header.stamp = ros::Time::now();
 //Set the goal pose to the i-th waypoint
  goal.target_pose.pose = task->target_pose_;
 //Start the robot moving toward the goal
  donavc_.sendGoal(goal, boost::bind(&TaskState::NavdoneCb, task, _1, _2),
             boost::bind(&TaskState::NavactiveCb,task),
             boost::bind(&TaskState::NavfeedbackCb,task, _1));
}

///无任务状态

FreeNavState::FreeNavState(){
  
}
FreeNavState::~FreeNavState(){
  
}
void FreeNavState::enter(TaskState *task)
{
  std::cout<<"enter tarfree nav"<<std::endl;
  donavc_.cancelAllGoals();//取消导航，也叫暂停
}
NavigationState *FreeNavState::handleInput(TaskState *task, NavInput input)
{
  switch (input)
  {
  case TARGET://目标状态
      return new TargetNavState();
  default:
    return NULL;
  }
}

///暂停状态

PauseNavState::PauseNavState(){
  
}
PauseNavState::~PauseNavState(){
  
}
void PauseNavState::enter(TaskState *task)
{
  std::cout<<"enter pause nav"<<std::endl;
  donavc_.cancelAllGoals();//取消导航，也叫暂停
}
NavigationState *PauseNavState::handleInput(TaskState *task, NavInput input)
{
  switch (input)
  {
  case TARGET://目标状态
      return new TargetNavState();
  case FREETAR://无目标状态
      return new FreeNavState();
  default:
    return NULL;
  }
}


