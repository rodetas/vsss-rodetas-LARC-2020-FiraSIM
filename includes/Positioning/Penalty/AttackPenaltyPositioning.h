//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_ATTACKPENALTYPOSITIONING_H
#define SDK_RODETAS_ATTACKPENALTYPOSITIONING_H

#include <Agent.h>

class AttackPenaltyPositioning : public Agent {

    vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase) override;
    vss::Pose defineTargetAndArrivalOrientation() override;

};

#endif //SDK_RODETAS_ATTACKPENALTYPOSITIONING_H
