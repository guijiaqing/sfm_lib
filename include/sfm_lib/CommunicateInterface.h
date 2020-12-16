#ifndef __COMUSTATE_H__
#define __COMUSTATE_H__
#include "StateControl.h"
#include "TaskState.h"
#include "Robot.h"
#include "sfm_lib/targets_list.h"
#include "sfm_lib/DisplayInput.h"


    ///导航状态父状态
class Robot;
class CommunicateInterface
{
private:
    ros::NodeHandle nh_;
    ros::Subscriber clicked_point_sut_;
    ros::ServiceServer target_pose_list_srv_;//路径点设置服务
    ros::Subscriber display_signal_sub_;//界面信号接收
    //ros::Publisher        marker_pub_;//
    Robot *robot_;

    bool deal_GetNavTargets(sfm_lib::targets_list::Request  &req,
         sfm_lib::targets_list::Response &res);  
    void DisplaySignalCb(const sfm_lib::DisplayInputConstPtr &signal);  
public:
    CommunicateInterface(ros::NodeHandle &nh,Robot *robot);
    ~CommunicateInterface();

};
#endif
