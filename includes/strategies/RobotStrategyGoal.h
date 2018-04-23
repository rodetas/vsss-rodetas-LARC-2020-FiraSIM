//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOSTRATEGYGOAL_H
#define SDK_RODETAS_ROBOSTRATEGYGOAL_H

#include "common.h"
#include "RobotStrategy.h"

using namespace common;

class RobotStrategyGoal : public RobotStrategy {

public:

    RobotStrategyGoal();

    Command specificStrategy(Command) override;
    btVector3 defineTarget() override;


};

#endif //SDK_RODETAS_ROBOSTRATEGYGOAL_H
