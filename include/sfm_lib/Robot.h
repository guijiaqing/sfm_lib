#ifndef __ROBOT_HEAD__
#define __ROBOT_HEAD__
#include "StateControl.h"
#include "CommunicateInterface.h"
#include "TaskState.h"
#include "sfm_lib/targets_list.h"
//#include "DealInput.h"

#define OLD_QUEUE_LEN 10  //允许保存的历史操作长度
class CommunicateInterface;
class TaskState;
class DealInput;
class Robot{
  public:
    Robot(ros::NodeHandle &nh);
    ~Robot();
    ros::NodeHandle nh_;
    RobotStation robot_state_;//机器整机状态
    TaskState* taskState_;//状态指针
    CommunicateInterface *comm_;//通讯接口
    //DealInput *dealiput_;//输入处理接口
    std::queue<TaskState*> taskqueue_;//任务队列，先进先出
    std::stack<TaskState*> taskstack_old_;//历史任务队列，固定长度，用于撤销使用

    sfm_lib::targets_list::Request task_date_v_;//任务请求数据
    
    TaskState* nextTask_do();//执行下一个任务
    TaskState* unTask_do();//执行已经执行过的上一个任务，相当于撤销
    void task_Copy2Old(TaskState *);//备份已经执行的任务

    void set_RobotStation(RobotStation sta);//设置机器人整机状态
    RobotStation get_RobotStation();//获取机器人整机状态

    void changeTask(TaskInput task_input);//任务切换

    int clear_Task();//清空任务
    void add_Task(std::string taskname = "robot-init");//添加初始化任务
    void add_Task(sfm_lib::targets_list::Request &targetTask);//添加执行任务
    //void add_Task(std::string taskname, geometry_msgs::Pose &targetPose);//添加纯导航任务
};

#endif
