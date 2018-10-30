//
// Created by paulo on 30/10/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYSINGLEATTACK_H
#define SDK_RODETAS_ROBOTSTRATEGYSINGLEATTACK_H

#include "RobotStrategy.h"

class RobotStrategySingleAttack : public RobotStrategy {

public:

    RobotStrategySingleAttack();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;
    float applyUnivectorField(vss::Pose) override;
};

#endif //SDK_RODETAS_ROBOTSTRATEGYSINGLEATTACK_H
