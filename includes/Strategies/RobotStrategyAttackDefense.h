//
//created by Samuel on 28/09/18
//

#ifndef SDK_RODETAS_ROBOTSTRATEGATTACKDEFENSE_H
#define SDK_RODETAS_ROBOTSTRATEGATTACKDEFENSE_H

#include <Strategies/RobotStrategy.h>
#include <iostream>

class RobotStrategyAttackDefense : public RobotStrategy {

public:
     RobotStrategyAttackDefense();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;
    float applyUnivectorField(vss::Pose) override;
};

#endif //SDK_RODETAS_ROBOTSTRATEGYATTACKDEFENSE_H