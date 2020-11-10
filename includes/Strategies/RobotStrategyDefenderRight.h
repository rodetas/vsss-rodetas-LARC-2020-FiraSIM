//
// Created by leonardo on 19/09/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYDEFENDERRIGHT_H
#define SDK_RODETAS_ROBOTSTRATEGYDEFENDERRIGHT_H

#include <Strategies/RobotStrategy.h>

class RobotStrategyDefenderRight : public RobotStrategy {

public:

    RobotStrategyDefenderRight();

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;

    vss::Pose defineTarget() override;

    float applyUnivectorField(vss::Pose) override;

    vss::WheelsCommand stopStrategy(vss::WheelsCommand) override;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYDEFENDERRIGHT_H
