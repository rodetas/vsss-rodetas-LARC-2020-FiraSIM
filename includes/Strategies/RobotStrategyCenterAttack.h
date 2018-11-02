//
//created by Samuel on 04/10/18
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYCENTERATTACK_H
#define SDK_RODETAS_ROBOTSTRATEGYCENTERATTACK_H

#include <Strategies/RobotStrategy.h>
#include <iostream>

class RobotStrategyCenterAttack : public RobotStrategy {

public:
     RobotStrategyCenterAttack();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;
    float applyUnivectorField(vss::Pose) override;

private:
    bool stopCenterAttacker;
};

#endif //SDK_RODETAS_ROBOTSTRATEGYCENTERATTACK_H