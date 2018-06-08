//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOSTRATEGYGOAL_H
#define SDK_RODETAS_ROBOSTRATEGYGOAL_H

#include "Common.h"
#include "RobotStrategy.h"

using namespace common;

class RobotStrategyGoal : public RobotStrategy {

public:

    RobotStrategyGoal();

    Command specificStrategy(Command) override;
    btVector3 defineTarget() override;
    float applyUnivectorField(btVector3) override;
    btVector3 defineArrivalOrientation(btVector3) override;
    Command stopStrategy(Command) override;



};

#endif //SDK_RODETAS_ROBOSTRATEGYGOAL_H
