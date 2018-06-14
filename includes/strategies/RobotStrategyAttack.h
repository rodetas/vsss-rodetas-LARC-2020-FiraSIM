//
// Created by manoel on 18/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYATTACK_H
#define SDK_RODETAS_ROBOTSTRATEGYATTACK_H

#include "RobotStrategy.h"

class RobotStrategyAttack : public RobotStrategy {

public:

    RobotStrategyAttack();

    Command specificStrategy(Command) override;
    vss::Pose defineTarget() override;
    float applyUnivectorField(vss::Pose) override;
    vss::Point defineArrivalOrientation(vss::Pose) override;


};

#endif //SDK_RODETAS_ROBOTSTRATEGYATTACK_H
