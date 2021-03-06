//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOSTRATEGYGOAL_H
#define SDK_RODETAS_ROBOSTRATEGYGOAL_H

#include "RobotStrategy.h"

class RobotStrategyGoal : public RobotStrategy {

public:

    RobotStrategyGoal();

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

    float applyUnivectorField(vss::Pose) override;
    vss::WheelsCommand stopStrategy(vss::WheelsCommand) override;

private:
    bool stopGoalKeeper;


};

#endif //SDK_RODETAS_ROBOSTRATEGYGOAL_H
