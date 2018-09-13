//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_ATTACKPENALTYPOSITIONING_H
#define SDK_RODETAS_ATTACKPENALTYPOSITIONING_H

#include <RobotPositioning.h>

class AttackPenaltyHitPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTargetAndArrivalOrientation() override;

};

#endif //SDK_RODETAS_ATTACKPENALTYPOSITIONING_H
