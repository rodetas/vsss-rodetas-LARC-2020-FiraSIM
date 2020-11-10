//
// Created by samuel on 10/10/18.
//

#ifndef SDK_RODETAS_ATTACKMIDDLEATTACKPOSITIONING_H
#define SDK_RODETAS_ATTACKMIDDLEATTACKPOSITIONING_H

#include <RobotPositioning.h>

class AttackMiddleAttackPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_ATTACKMIDDLEATTACKPOSITIONING_H
