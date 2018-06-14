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
    vss::Pose defineTarget() override;

    float applyUnivectorField(vss::Pose) override;
    vss::Point defineArrivalOrientation(vss::Pose) override;
    Command stopStrategy(Command) override;

};

#endif //SDK_RODETAS_ROBOSTRATEGYGOAL_H
