//
// Created by manoel on 22/08/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYDEFENDERBACK_H
#define SDK_RODETAS_ROBOTSTRATEGYDEFENDERBACK_H

#include "RobotStrategy.h"

class RobotStrategyDefenderBack : public RobotStrategy {

public:

    RobotStrategyDefenderBack();

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTargetAndArrivalOrientation() override;

    float applyUnivectorField(vss::Pose) override;
    vss::WheelsCommand stopStrategy(vss::WheelsCommand) override;


};

#endif //SDK_RODETAS_ROBOTSTRATEGYDEFENDERBACK_H
