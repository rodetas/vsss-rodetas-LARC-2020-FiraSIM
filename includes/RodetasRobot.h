//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <RodetasState.h>
#include <common.h>
#include <RobotState.h>
#include <RobotDebug.h>
#include <strategies/RobotStrategy.h>
#include <MathHelper.h>
#include <cmath>
#include <strategies/RobotStrategyAttack.h>
//#include <strategies/StrategyDefense.h>
//#include <strategies/StrategyGoal.h>
//#include <strategies/RobotStrategyBase.h>

using namespace common;

class RodetasRobot {

public:

    RodetasRobot();

    void calcAction();

    void updateSelfState(RobotState);
    void updateState(RodetasState);

    void setDebug(RobotDebug);
    void setStrategy(RobotStrategy*);

    Command getCommand();
    RobotDebug getRobotDebug();
    RobotState getSelfState();

private:

    Command command;
    RodetasState state;
    RobotDebug debug;
    RobotState selfState;
    RobotStrategy* strategy;

};


#endif //SDK_RODETAS_RODETASROBOT_H
