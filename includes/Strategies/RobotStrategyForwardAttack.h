//
//created by Samuel on 28/09/18
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFORWARDATTACK_H
#define SDK_RODETAS_ROBOTSTRATEGYFORWARDATTACK_H

#include <Strategies/RobotStrategy.h>
#include <iostream>

class RobotStrategyForwardAttack : public RobotStrategy {

public:
     RobotStrategyForwardAttack();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTargetAndArrivalOrientation() override;
    float applyUnivectorField(vss::Pose) override;
};

#endif //SDK_RODETAS_ROBOTSTRATEGYFORWARDATTACK_H