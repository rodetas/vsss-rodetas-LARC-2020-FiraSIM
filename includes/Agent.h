//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_AGENT_H
#define SDK_RODETAS_AGENT_H

#include <Domain/RodetasState.h>
#include <Strategies/RobotStrategyBase.h>
#include <Domain/WheelsCommand.h>
#include <Domain/Pose.h>
#include <Domain/Path.h>

class Agent {

public:

    virtual vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase) = 0;
    virtual vss::Pose defineTarget() = 0;
    virtual float applyUnivectorField(vss::Pose) = 0;

    virtual vss::WheelsCommand getCommand(){
        return command;
    };

    virtual vss::Pose getFinalPose() {
        return target;
    };

    virtual vss::Point getStepPose() {
        return stepPose;
    };

    virtual vss::Path getPath() {
        return path;
    };

protected:

    vss::WheelsCommand command;

    vss::Pose target;
    vss::Point arrivalOrientation;
    vss::Point stepPose;
    vss::Path path;

    RobotStrategyBase strategyBase;
    RobotState robot;
    RodetasState state;

};

#endif //SDK_RODETAS_AGENT_H
