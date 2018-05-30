//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
#define SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H

#include <Common.h>
#include <strategies/RobotStrategy.h>

using namespace common;

class RobotStrategyDefender : public RobotStrategy {

public:

    RobotStrategyDefender();

    Command specificStrategy(Command) override;

    btVector3 defineTarget() override;

    float applyUnivectorField(btVector3) override;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
