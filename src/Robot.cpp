#include "Robot.h"
Robot::Robot(ros::NodeHandle &nh):nh_(nh),robot_state_(NORMAL){//整机状态normal
  ROS_INFO("no param robot");
  comm_ = new CommunicateInterface(nh,this);
  add_Task();//默认加入Init_task 到 queueTask
}

Robot::~Robot(){
  clear_Task();//清理内存
}
TaskState* Robot::nextTask_do(){//返回下一个任务
  task_Copy2Old(taskState_);//删除之前，保存当前任务
  if(!taskqueue_.empty()){//有任务
      ROS_INFO("take one task in list");
      return taskqueue_.front();//取任务
  }else{//没有任务
      return new FreeTaskState();//空闲状态
      return NULL;
  }
}

void Robot::task_Copy2Old(TaskState *tasks){//备份已经执行的任务
  taskstack_old_.push(tasks);//把当前的存起来
  ROS_INFO("pop one task in list");
  taskqueue_.pop();//删除当前任务
}
TaskState* Robot::unTask_do(){//执行已经执行过的上一个任务，相当于撤销
}

void Robot::set_RobotStation(RobotStation sta){//设置机器人整机状态
  robot_state_ = sta;
}
RobotStation Robot::get_RobotStation(){//获取机器人整机状态
  return robot_state_;
}

int Robot::clear_Task(){//清空任务
  while(!taskqueue_.empty()){
      delete taskqueue_.front();
      taskqueue_.pop();
  }
  while(!taskstack_old_.empty()){
      delete taskstack_old_.top();
      taskstack_old_.pop();
  }
}

void Robot::add_Task(std::string taskname){//添加初始化任务
  InitTaskState *initptr = new InitTaskState();//初始化任务
  initptr->task_name_ =  taskname;//给任务命名
  initptr->init_nav_input = FREETAR;//给导航初始化输入
  taskState_ = initptr;
  taskState_->enter(this);
  //taskqueue_.push(initptr);//添加任务
}
void Robot::add_Task(sfm_lib::targets_list::Request &targetTask){//添加执行任务
  ROS_INFO("add task queue 2:%d",(int)(taskqueue_.size()));
  while (!taskqueue_.empty()) taskqueue_.pop();
  taskqueue_.push(new FreeTaskState());
  int task_len = targetTask.target_points.size();
  for(int i=0;i<task_len;i++){
    ROS_INFO("0");
    OneTaskState *taskptr = new OneTaskState();
    ROS_INFO("1");
    taskptr->task_name_ = "oneTask-"+std::to_string(i);//任务名称
    taskptr->target_pose_ =  targetTask.target_points[i];//目标位姿
    taskptr->init_nav_input = TARGET;//导航目标状态
    ROS_INFO("2");
    taskqueue_.push(taskptr);//添加任务
    ROS_INFO("3");
  }
  ROS_INFO("add task queue 1:%d",task_len);
  ROS_INFO("add task queue 2:%d",(int)(taskqueue_.size()));
}

void Robot::changeTask(TaskInput task_input){//任务切换
  ROS_INFO("enter changefun");
  TaskState* tasknew = taskState_->handleInput(this,task_input);
  if(tasknew!=NULL){
    ROS_INFO("changefun delete");  
    delete taskState_;
    taskState_ = tasknew;
    taskState_->enter(this);
  }
  ROS_INFO("changefun done"); 
}


    

