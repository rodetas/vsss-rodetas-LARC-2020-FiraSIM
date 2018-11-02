//
// Created by leonardo on 19/10/18.
//

#ifndef SDK_RODETAS_ATTACKFREEBALLRIGHTATTACKPOSITIONING_H
#define SDK_RODETAS_ATTACKFREEBALLRIGHTATTACKPOSITIONING_H

#include <RobotPositioning.h>

class AttackFreeballRightAttackPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_ATTACKFREEBALLRIGHTATTACKPOSITIONING_H
