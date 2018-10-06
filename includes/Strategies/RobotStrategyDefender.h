//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
#define SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H

#include <Strategies/RobotStrategy.h>

class RobotStrategyDefender : public RobotStrategy {

public:

    RobotStrategyDefender();

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;

    vss::Pose defineTarget() override;

    float applyUnivectorField(vss::Pose) override;

    vss::WheelsCommand stopStrategy(vss::WheelsCommand) override;
};

#endif //SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
