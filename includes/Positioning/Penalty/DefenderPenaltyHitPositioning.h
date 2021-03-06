//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_DEFENDERPENALTYPOSITIONING_H
#define SDK_RODETAS_DEFENDERPENALTYPOSITIONING_H

#include <RobotPositioning.h>

class DefenderPenaltyHitPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_DEFENDERPENALTYPOSITIONING_H
