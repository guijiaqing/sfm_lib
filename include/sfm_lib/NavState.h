#ifndef  __NAVSTATE_H__
#define __NAVSTATE_H__
#include "StateControl.h"
//#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_listener.h>
#include "TaskState.h"
//typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> DoNavClient;
    ///导航状态父状态
class TaskState;
class NavigationState
{
private:
    int a;
public:
    NavigationState();
    ~NavigationState();
    DoNavClient donavc_;  
    std::vector<int> ve_;

    virtual void enter(TaskState *task) = 0;//this is a pure virtual func
    virtual NavigationState* handleInput(TaskState* task,NavInput input);
};

///目标点状态
class TargetNavState : public NavigationState
{
private:
    void move_base_sendgoal(TaskState *task);//发送导
public:
    TargetNavState(/* args */);
    ~TargetNavState();
    virtual void enter(TaskState *task) ;
    virtual NavigationState* handleInput(TaskState *task,NavInput input);
};

///无任务状态
class FreeNavState : public NavigationState
{
private:
public:
    FreeNavState(/* args */);
    ~FreeNavState();
    virtual void enter(TaskState *task) ;
    virtual NavigationState* handleInput(TaskState *task,NavInput input);
};


///暂停状态
class PauseNavState : public NavigationState
{
private:
public:
    PauseNavState(/* args */);
    ~PauseNavState();
    virtual void enter(TaskState *task) ;
    virtual NavigationState* handleInput(TaskState *task,NavInput input);
};

#endif
