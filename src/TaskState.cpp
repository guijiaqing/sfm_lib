#include <stddef.h>
#include <iostream>
#include "TaskState.h"
///父状态下默认只能进入初始化状态任务
TaskState::TaskState()
{
    nav_state_ = new FreeNavState();
}
TaskState::~TaskState()
{

}
TaskState* TaskState::handleInput(Robot *robot,TaskInput input)
{

}
void TaskState::exitState(TaskState* task)
{
 
}
void TaskState::change_navState(TaskState *task,NavInput init_nav_input){//改变导航状态
  NavigationState *nav_state = task->nav_state_->handleInput(task,init_nav_input);
  if(nav_state!=NULL){
    delete task->nav_state_;
    task->nav_state_ = nav_state;
    task->nav_state_->enter(task);
  }
}

 void TaskState::NavdoneCb(const actionlib::SimpleClientGoalState &state,const move_base_msgs::MoveBaseResultConstPtr &result)
 {
     
     
 }//一次导航完成执行
 void TaskState::NavactiveCb()
 {
   
    
 }//激活触发一次
 void TaskState::NavfeedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
 {


 }//期间一直触发


///初始化状态
InitTaskState::InitTaskState()
{
  ROS_INFO("init_task");
}
InitTaskState::~InitTaskState()
{

}
void InitTaskState::enter(Robot *robot) 
{
  std::cout<<"enter InitState"<<std::endl;
}
TaskState* InitTaskState::handleInput(Robot *robot,TaskInput input)
{
    switch (input)
    {
    case RETRUN_DOCK://返航
    case INSERT_TASK://临时插入任务
    case ADD_TASK://任务更新
      return new ADDTaskState();
    default:
      return NULL;
    }
}

///任务添加状态
ADDTaskState::ADDTaskState()
{
  ROS_INFO("add_task");
}
ADDTaskState::~ADDTaskState()
{

}
void ADDTaskState::enter(Robot *robot) 
{
  ROS_INFO("enter addTaskState");
  robot->add_Task(robot->task_date_v_);//添加执行任务
}
TaskState* ADDTaskState::handleInput(Robot *robot,TaskInput input)
{
    switch (input)
    {
    case RETRUN_DOCK://返航
    case INSERT_TASK://临时插入任务
      ROS_INFO("add -> input insert");
      return NULL;
    case STA_TASK://开始
      ROS_INFO("add -> input start");
      return robot->nextTask_do();//执行下一个任务
    case END_TASK://任务取消
    default:
      return NULL;
    }
}

///空闲状态
FreeTaskState::FreeTaskState()
{
  ROS_INFO("free_task");
}
FreeTaskState::~FreeTaskState()
{

}
void FreeTaskState::enter(Robot *robot) 
{
  ROS_INFO("enter Free State");
}
TaskState* FreeTaskState::handleInput(Robot *robot,TaskInput input)
{
    ROS_INFO("enter Free State handle");
    switch (input)
    {
    case RETRUN_DOCK://返航
      ROS_INFO("return return");
      return new ReturnTaskState();
    case INSERT_TASK://临时插入任务
      ROS_INFO("return INSERT");
      return NULL;
    case RESTA_TASK://重新开始
      ROS_INFO("return RESET");
    case ADD_TASK://任务更新
      ROS_INFO("return ADD");
      return new ADDTaskState();
    default:
      ROS_INFO("return NULL");
      return NULL;
    }
}

///返航状态
ReturnTaskState::ReturnTaskState()
{
  ROS_INFO("init return_task");
}
ReturnTaskState::~ReturnTaskState()
{
  ROS_INFO("return_task delete");
}
void ReturnTaskState::enter(Robot *robot) 
{
     std::cout<<"enter return State"<<std::endl;
}
TaskState* ReturnTaskState::handleInput(Robot *robot,TaskInput input)
{
    switch (input)
    {
    case END_TASK://结束任务
    case INSERT_TASK://临时插入任务
    case STA_TASK://开始，继续
    case PAUSE_TASK://暂停
    default:
      return NULL;
    }
}

///命令状态
CmdTaskState::CmdTaskState()
{
  ROS_INFO("new cmd_state");
}
CmdTaskState::~CmdTaskState()
{
  ROS_INFO("cmd_state delete");
}
void CmdTaskState::enter(Robot *robot) 
{
     std::cout<<"enter cmd State"<<std::endl;
}
TaskState* CmdTaskState::handleInput(Robot *robot,TaskInput input)
{
    switch (input)
    {
    case END_TASK://结束任务
    case INSERT_TASK://临时插入任务
    case STA_TASK://开始，继续
    case PAUSE_TASK://暂停
    default:
      return NULL;
    }
}


///任务状态
OneTaskState::OneTaskState()
{
  ROS_INFO("create nav_task");
}
OneTaskState::~OneTaskState()
{

}
void OneTaskState::enter(Robot *robot) 
{
  ROS_INFO("enter one Task");
  robot_ = robot;//任务对象保存
  change_navState(this,init_nav_input);
   
}
TaskState* OneTaskState::handleInput(Robot *robot,TaskInput input)
{
    switch (input)
    {
    case RETRUN_DOCK://返航
      return NULL;
    case CHARGE://充电
      return NULL;
    case INSERT_TASK://临时插入任务
      return NULL;
    case RESTA_TASK://重新开始
      return NULL;
    case END_TASK://任务取消
      return task_Cancel();
    case STA_TASK://开始、继续
      return task_Begin();
    case PAUSE_TASK://暂停任务
      return task_Pause();
    case NEXT_TASK://下一个任务
      ROS_INFO("return next task in taskcpp");
      return robot->nextTask_do();
    default:
      return NULL;
    }    
}
TaskState* OneTaskState::task_Cancel(){//任务取消执行
  change_navState(this,NavInput::FREETAR);
  return new FreeTaskState();
}
TaskState* OneTaskState::task_Pause(){//任务暂停
  change_navState(this,NavInput::PAUSE);
  return NULL;
}
TaskState* OneTaskState::task_Begin(){//任务继续
  change_navState(this,NavInput::TARGET);
  return NULL;
}
 void OneTaskState::NavdoneCb(const actionlib::SimpleClientGoalState &state,const move_base_msgs::MoveBaseResultConstPtr &result)
 {
    ROS_INFO("one task finished ");   
    robot_->changeTask(TaskInput::NEXT_TASK);
     
 }//一次导航完成执行
 void OneTaskState::NavactiveCb()
 {
   
    
 }//激活触发一次
 void OneTaskState::NavfeedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
 {
    ROS_INFO("one task doing ");

 }//期间一直触发

