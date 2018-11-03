//
// Created by leonardo on 19/10/18.
//

#ifndef SDK_RODETAS_ATTACKFREEBALLLEFTDEFENSEPOSITIONING_H
#define SDK_RODETAS_ATTACKFREEBALLLEFTDEFENSEPOSITIONING_HH

#include <RobotPositioning.h>

class AttackFreeballLeftDefensePositioning : public RobotPositioning {
    

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_ATTACKFREEBALLLEFTDEFENSEPOSITIONING_H
