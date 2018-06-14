//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGY_H
#define SDK_RODETAS_ROBOTSTRATEGY_H

#include <Common.h>
#include "RobotStrategyBase.h"
#include <Domain/RobotState.h>
#include <Domain/RodetasState.h>
#include <Movimentation.h>
#include <UnivectorField.h>
#include <Domain/Pose.h>
#include <Domain/Path.h>
#include "Config.h"

using namespace common;

class RobotStrategy {

public:
    RobotStrategy();

    virtual Command applyStrategy(RobotState, RodetasState, RobotStrategyBase);

    virtual Command specificStrategy(Command) = 0;

    virtual vss::Pose defineTarget() = 0;

    virtual float applyUnivectorField(vss::Pose) = 0;

    virtual vss::Point defineArrivalOrientation(vss::Pose) = 0;

    //@TODO: inserir comentarios em cada estrategia
    virtual Command cornerStrategy(Command);

    virtual Command stopStrategy(Command);

    virtual Command blockedStrategy(Command);

    virtual Command kickStrategy(Command);

    Command getCommand();
    vss::Pose getFinalPose();
    vss::Point getStepPose();
    vss::Path getPath();

protected:
    RobotStrategyBase strategyBase;

    Command command;

    vss::Pose target;
    vss::Point stepPose;
    vss::Path path;

    RobotState robot;
    RodetasState state;

    Movimentation* movimentation;

};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
