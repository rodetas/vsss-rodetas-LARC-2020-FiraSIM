//
// Created by manoel on 14/09/18.
//

#include "Positioning/Penalty/DefenderPenaltyAgainstPositioning.h"

vss::WheelsCommand DefenderPenaltyAgainstPositioning::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c, vss::Point(vss::MAX_COORDINATE_X, vss::MAX_COORDINATE_Y/2));

    return c;
}

vss::Pose DefenderPenaltyAgainstPositioning::defineTargetAndArrivalOrientation() {
    vss::Pose target(vss::MAX_COORDINATE_X/2-10, vss::MAX_COORDINATE_Y*0.7, 0);

    return target;
}