//
// Created by leonardo on 19/10/18.
//

#ifndef SDK_RODETAS_ATTACKFREEBALLRIGHTDEFENSEPOSITIONING_H
#define SDK_RODETAS_ATTACKFREEBALLRIGHTDEFENSEPOSITIONING_HH

#include <RobotPositioning.h>

class AttackFreeballRightDefensePositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_ATTACKFREEBALLRIGHTDEFENSEPOSITIONING_H
