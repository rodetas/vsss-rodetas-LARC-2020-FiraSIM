//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <RodetasState.h>
#include <Common.h>
#include <RobotState.h>
#include <RobotDebug.h>
#include <strategies/RobotStrategy.h>
#include <MathHelper.h>
#include <cmath>
#include <strategies/RobotStrategyAttack.h>
#include "Mindset.h"

using namespace common;

class RodetasRobot {

public:

    RodetasRobot();
    RodetasRobot(int, MindSet);

    void calcAction();

    void updateSelfState(RobotState);
    void updateState(RodetasState);

    void setDebug(RobotDebug);
    void setStrategy(RobotStrategy*);

    int getId();

    Command getCommand();
    RobotDebug getRobotDebug();
    RobotState getSelfState();
    RobotStrategyBase getRobotStrategyBase();

    MindSet getMindSet();
    void setMindSet(MindSet);

private:

    int id;

    Command command;
    RodetasState state;
    RobotDebug debug;
    RobotState selfState;
    RobotStrategy* strategy;
    RobotStrategyBase strategyBase;
    MindSet mindSet;

};


#endif //SDK_RODETAS_RODETASROBOT_H
