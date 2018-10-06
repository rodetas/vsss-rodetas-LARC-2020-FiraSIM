//
// Created by manoel on 14/09/18.
//

#ifndef SDK_RODETAS_DEFENDERPENALTYAGAINSTPOSITIONING_H
#define SDK_RODETAS_DEFENDERPENALTYAGAINSTPOSITIONING_H

#include <RobotPositioning.h>

class DefenderPenaltyAgainstPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_DEFENDERPENALTYAGAINSTPOSITIONING_H
