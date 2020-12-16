#ifndef __EXECSTATE_H__
#define __EXECSTATE_H__
#include "StateControl.h"
#include "Robot.h"

class Robot;
class DealInput
{
private:
    /* data */
public:
    DealInput(Robot &robot);
    ~DealInput();
    Robot robot_;
};
#endif
