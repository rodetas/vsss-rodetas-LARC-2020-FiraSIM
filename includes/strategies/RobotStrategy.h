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
#include <Domain/Constants.h>

using namespace common;

class RobotStrategy {

public:
    RobotStrategy();

    virtual vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase);

    virtual vss::WheelsCommand specificStrategy(vss::WheelsCommand) = 0;

    virtual vss::Pose defineTarget() = 0;

    virtual float applyUnivectorField(vss::Pose) = 0;

    virtual vss::Point defineArrivalOrientation(vss::Pose) = 0;

    //@TODO: inserir comentarios em cada estrategia
    virtual vss::WheelsCommand cornerStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand stopStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand blockedStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand kickStrategy(vss::WheelsCommand);

    vss::WheelsCommand getCommand();
    vss::Pose getFinalPose();
    vss::Point getStepPose();
    vss::Path getPath();

protected:
    RobotStrategyBase strategyBase;

    vss::WheelsCommand command;

    vss::Pose target;
    vss::Point stepPose;
    vss::Path path;

    RobotState robot;
    RodetasState state;

    Movimentation movimentation;

};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
