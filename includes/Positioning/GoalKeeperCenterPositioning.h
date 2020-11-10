//
// Created by manoel on 12/09/18.
//

#ifndef SDK_RODETAS_GOALKEEPERCENTERPOSITIONING_H
#define SDK_RODETAS_GOALKEEPERCENTERPOSITIONING_H

#include <RobotPositioning.h>

class GoalKeepCenterPositioning : public RobotPositioning {

    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;

};

#endif //SDK_RODETAS_GOALKEEPERCENTERPOSITIONING_H





//
