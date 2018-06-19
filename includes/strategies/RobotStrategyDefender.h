//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
#define SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H

#include <Common.h>
#include <strategies/RobotStrategy.h>

using namespace common;

class RobotStrategyDefender : public RobotStrategy {

public:

    RobotStrategyDefender();

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;

    vss::Pose defineTarget() override;

    float applyUnivectorField(vss::Pose) override;

    vss::Point defineArrivalOrientation(vss::Pose) override;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYDEFENDER_H
