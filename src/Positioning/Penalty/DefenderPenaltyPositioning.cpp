//
// Created by manoel on 12/09/18.
//

#include "Positioning/Penalty/DefenderPenaltyPositioning.h"

vss::WheelsCommand DefenderPenaltyPositioning::specificStrategy(vss::WheelsCommand) {

    command.leftVel *= 0.5;
    command.rightVel *= 0.5;

    return command;

}

vss::Pose DefenderPenaltyPositioning::defineTargetAndArrivalOrientation() {

    target = vss::Pose(100,65,0);
    arrivalOrientation = vss::Point(0, 65);

    return target;

}