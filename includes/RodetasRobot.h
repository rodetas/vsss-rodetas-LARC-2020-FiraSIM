//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <Domain/RodetasState.h>
#include <Common.h>
#include <Domain/RobotState.h>
#include <Domain/Debug.h>
#include <strategies/RobotStrategy.h>
#include <Helpers/MathHelper.h>
#include <cmath>
#include <strategies/RobotStrategyAttack.h>
#include "Domain/Mindset.h"

using namespace common;

class RodetasRobot {

public:

    RodetasRobot();
    RodetasRobot(int, MindSet);

    void calcAction();

    void updateSelfState(RobotState);
    void updateState(RodetasState);

    void setStrategy(RobotStrategy*);

    int getId();

    Command getCommand();
    RobotState getSelfState();
    RobotStrategyBase getRobotStrategyBase();

    MindSet getMindSet();
    void setMindSet(MindSet);

    vss::Path getPath();
    vss::Pose getFinalPose();
    vss::Point getStepPoint();

private:

    int id;

    Command command;
    RodetasState state;
    RobotState selfState;
    RobotStrategy* strategy;
    RobotStrategyBase strategyBase;
    MindSet mindSet;

    vss::Path path;
    vss::Pose target;
    vss::Point stepPoint;

};


#endif //SDK_RODETAS_RODETASROBOT_H
