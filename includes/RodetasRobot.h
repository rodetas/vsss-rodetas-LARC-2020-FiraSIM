//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <Domain/RodetasState.h>
#include <Domain/RobotState.h>
#include <Domain/Debug.h>
#include "Domain/Mindset.h"
#include <Strategies/RobotStrategy.h>
#include <Strategies/RobotStrategyAttack.h>
#include <Helpers/MathHelper.h>

class RodetasRobot {

public:

    RodetasRobot();
    RodetasRobot(int, MindSet, Agent*);

    void calcAction();

    void updateSelfState(RobotState);
    void updateState(RodetasState);

    void setStrategy(RobotStrategy*);

    int getId();

    vss::WheelsCommand getCommand();
    RobotState getSelfState();
    RobotStrategyBase getRobotStrategyBase();

    MindSet getMindSet();
    void setMindSet(MindSet);

    vss::Path getPath();
    vss::Pose getFinalPose();
    vss::Point getStepPoint();

private:

    int id;

    RodetasState state;
    RobotState selfState;
    Agent* agent;
    RobotStrategyBase strategyBase;
    MindSet mindSet;

    vss::WheelsCommand command;
    vss::Path path;
    vss::Pose target;
    vss::Point stepPoint;

};


#endif //SDK_RODETAS_RODETASROBOT_H
