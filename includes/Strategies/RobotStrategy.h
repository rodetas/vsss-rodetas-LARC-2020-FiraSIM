//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGY_H
#define SDK_RODETAS_ROBOTSTRATEGY_H

#include <Domain/RobotState.h>
#include <Domain/RodetasState.h>
#include <Domain/Pose.h>
#include <Domain/Path.h>
#include <Domain/Constants.h>
#include <Strategies/RobotStrategyBase.h>
#include <Movements/Movimentation.h>
#include <Movements/UnivectorField.h>

class RobotStrategy {

public:
    RobotStrategy();

    virtual vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase);

    virtual vss::WheelsCommand specificStrategy(vss::WheelsCommand) = 0;

    virtual vss::Pose defineTargetAndArrivalOrientation() = 0;

    virtual float applyUnivectorField(vss::Pose) = 0;

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
    vss::Point arrivalOrientation;
    vss::Point stepPose;
    vss::Path path;

    RobotState robot;
    RodetasState state;

    Movimentation movimentation;

};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
