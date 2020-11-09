//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <Domain/RodetasState.h>
#include <Domain/RobotState.h>
#include <Domain/Debug.h>
#include "Domain/Mindset.h"
#include <Domain/RobotSpeed.h>
#include <Strategies/RobotStrategy.h>
#include <Strategies/RobotStrategyAttack.h>
#include <Strategies/RobotStrategySideAttack.h>
#include <Strategies/RobotStrategyCenterAttack.h>
#include <Strategies/RobotStrategyForwardAttack.h>
#include <Helpers/MathHelper.h>
#include <Domain/PositionStatus.h>

class RodetasRobot {

public:

    RodetasRobot();
    RodetasRobot(int, MindSet, Agent*);

    void calcAction();

    void updateSelfState(RobotState);
    void updateState(RodetasState);

    void setStrategy(Agent*);

    int getId();

    vss::WheelsCommand getCommand();
    RobotState getSelfState();
    RobotStrategyBase getRobotStrategyBase();

    MindSet getMindSet();
    void setMindSet(MindSet);

    PositionStatus getPositionStatus();
    void setPositionStatus(PositionStatus);

    vss::Path getPath();
    vss::Pose getFinalPose();
    vss::Point getStepPoint();

    bool isNull();

private:

    int id;

    RodetasState state;
    RobotState selfState;
    Agent* agent;
    RobotStrategyBase strategyBase;
    MindSet mindSet;
    PositionStatus positionStatus;
    int robotSpeed;

    vss::WheelsCommand command;
    vss::Path path;
    vss::Pose target;
    vss::Point stepPoint;

};


#endif //SDK_RODETAS_RODETASROBOT_H
