#ifndef __STATE_CONTRL_H__
#define __STATE_CONTRL_H__

#include <geometry_msgs/PoseStamped.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_listener.h>
#include <stack>
#include <queue>
#include <vector>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> DoNavClient;

typedef enum {//机器人整机状态
  NORMAL,//正常
  WARNING,//报警
  LOWPOWER,//低电量
  ERROR//出错
}RobotStation;
enum TaskInput{//任务级别的状态输入
    INIT,//自检任务
    CHARGE,//充电任务
    RETRUN_DOCK,//返航任务
    INSERT_TASK,//临时插入的任务
    ADD_TASK,//任务更新
    STA_TASK,//开始任务
    NEXT_TASK,//下一个任务
    END_TASK,//结束任务
    PAUSE_TASK,//暂停任务
    RESTA_TASK,//重新开始
};
enum NavInput{//导航任务状态输入    
    TARGET,//目标点状态
    PAUSE,//暂停状态
    FREETAR,//无目标状态
};

enum ComInput{//交流任务状态输入
    ROSMSGIN,//ROS消息输入
    CLINK,//界面输入
    ROSMSGOUT,//ros消息输出
    DISPLAY//界面输出
};

#endif
