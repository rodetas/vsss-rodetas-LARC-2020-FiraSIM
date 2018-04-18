//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGY_H
#define SDK_RODETAS_ROBOTSTRATEGY_H

#include <common.h>
#include "RobotStrategyBase.h"
#include <RobotState.h>
#include <RodetasState.h>

using namespace common;

class RobotStrategy {

public:
    RobotStrategy();

    /**
     * Apply the robot strategy when it's on the corner
     */
    virtual Command corner_strategy(Command);

    virtual Command stop_strategy(Command);

    virtual Command blocked_strategy(Command);

    virtual Command kick_strategy(Command);

    Command getCommand();
    btVector3 getFinalPose();
    btVector3 getStepPose();
    Path getPath();

protected:
    RobotStrategyBase strategyBase;

    Command command;
    btVector3 finalPose;
    btVector3 stepPose;
    Path path;

    RobotState robot;
    RodetasState state;

    btVector3 ballProjection;
    btVector3 robotProjection;
};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
