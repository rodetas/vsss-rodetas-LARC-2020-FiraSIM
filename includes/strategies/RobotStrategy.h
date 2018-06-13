//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGY_H
#define SDK_RODETAS_ROBOTSTRATEGY_H

#include <Common.h>
#include "RobotStrategyBase.h"
#include <RobotState.h>
#include <RodetasState.h>
#include <Movimentation.h>

using namespace common;

class RobotStrategy {

public:
    RobotStrategy();

    virtual Command applyStrategy(RobotState, RodetasState, RobotStrategyBase);

    virtual Command specificStrategy(Command) = 0;

    virtual btVector3 defineTarget() = 0;

    //@TODO: inserir comentarios em cada estrategia
    virtual Command cornerStrategy(Command);

    virtual Command stopStrategy(Command);

    virtual Command blockedStrategy(Command);

    virtual Command kickStrategy(Command);

    Command getCommand();
    btVector3 getFinalPose();
    btVector3 getStepPose();
    Path getPath();

protected:
    RobotStrategyBase strategyBase;

    Command command;
    btVector3 target;
    btVector3 stepPose;
    Path path;

    RobotState robot;
    RodetasState state;

    Movimentation* movimentation;

    //@TODO: jogar imageSize e goalSize para Config
    btVector3 imageSize;
    btVector3 goalSize;
    btVector3 goalAreaSize;

};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
