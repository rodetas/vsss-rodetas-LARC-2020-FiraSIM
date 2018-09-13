//
// Created by manoel on 12/09/18.
//

#include "Positioning/Penalty/DefenderPenaltyHitPositioning.h"

vss::WheelsCommand DefenderPenaltyHitPositioning::specificStrategy(vss::WheelsCommand command) {

    return command;

}

vss::Pose DefenderPenaltyHitPositioning::defineTargetAndArrivalOrientation() {

    target = vss::Pose(100,65,0);

    return target;
}