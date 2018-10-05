//
// Created by manoel on 18/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYATTACK_H
#define SDK_RODETAS_ROBOTSTRATEGYATTACK_H

#include "RobotStrategy.h"

class RobotStrategyAttack : public RobotStrategy {

public:

    RobotStrategyAttack();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTargetAndArrivalOrientation() override;
    float applyUnivectorField(vss::Pose) override;

private:
	bool stopAttacker;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYATTACK_H
