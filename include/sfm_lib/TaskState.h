#ifndef __TASKSTATE_H__
#define __TASKSTATE_H__
#include "StateControl.h"
//#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "NavState.h"
#include "CommunicateInterface.h"
#include "Robot.h"

class Robot;
class NavigationState;
class TaskState
{
private:

public:
   TaskState();
   ~TaskState();
   NavigationState *nav_state_;
   //ros::NodeHandle nh_;
   Robot *robot_ = NULL;
   virtual void NavdoneCb(const actionlib::SimpleClientGoalState &state,const move_base_msgs::MoveBaseResultConstPtr &result);//一次导航完成执行
   virtual void NavactiveCb();//激活触发一次
   virtual void NavfeedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);//期间一直触发

   NavInput init_nav_input;//初始化导航状态
   geometry_msgs::Pose target_pose_ ;//任务点位姿
   std::string task_name_ ;//状态名称

   virtual void enter(Robot *robot)=0;//this is a pure virtual func
   virtual TaskState* handleInput(Robot *robot,TaskInput input);
   virtual void exitState(TaskState* task);//退出时执行

   virtual void change_navState(TaskState *task,NavInput init_nav_input);//改变导航状态
};

///初始化状态
class InitTaskState : public TaskState
{
private:
  /* data */
public:
  InitTaskState();
  ~InitTaskState();

  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};

///任务添加状态
class ADDTaskState : public TaskState
{
private:
  /* data */
public:
  ADDTaskState();
  ~ADDTaskState();

  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};

///空闲状态
class FreeTaskState : public TaskState
{
private:
  /* data */
public:
  FreeTaskState();
  ~FreeTaskState();

  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};

///返航状态
class ReturnTaskState : public TaskState
{
private:
  /* data */
public:
  ReturnTaskState();
  ~ReturnTaskState();

  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};

///命令状态
class CmdTaskState : public TaskState
{
private:

public:
  CmdTaskState();
  ~CmdTaskState();

  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};



///任务状态
class OneTaskState : public TaskState
{
private:

public:
  OneTaskState();
  ~OneTaskState();

  void NavdoneCb(const actionlib::SimpleClientGoalState &state,const move_base_msgs::MoveBaseResultConstPtr &result);//一次导航完成执行
  void NavactiveCb();//激活触发一次
  void NavfeedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);//期间一直触发
  TaskState* task_Cancel();//任务取消
  TaskState* task_Pause();//任务暂停
  TaskState* task_Begin();//任务继续
  virtual void enter(Robot *robot) ;
  virtual TaskState* handleInput(Robot *robot,TaskInput input);
};


#endif
