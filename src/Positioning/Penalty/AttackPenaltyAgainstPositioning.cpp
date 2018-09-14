//
// Created by manoel on 14/09/18.
//

#include "Positioning/Penalty/AttackPenaltyAgainstPositioning.h"

vss::WheelsCommand AttackPenaltyAgainstPositioning::specificStrategy(vss::WheelsCommand c) {
    // mantem robo virado para o gol
    c = stopStrategy(c, vss::Point(vss::MAX_COORDINATE_X, vss::MAX_COORDINATE_Y/2));
    return c;
}

vss::Pose AttackPenaltyAgainstPositioning::defineTargetAndArrivalOrientation(){
    vss::Pose target(vss::MAX_COORDINATE_X/2-10, vss::MAX_COORDINATE_Y*0.3, 0);

    return target;
}
