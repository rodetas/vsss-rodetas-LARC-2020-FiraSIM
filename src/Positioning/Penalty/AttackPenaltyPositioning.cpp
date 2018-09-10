//
// Created by manoel on 31/08/18.
//

#include "Positioning/Penalty/AttackPenaltyPositioning.h"

vss::Pose AttackPenaltyPositioning::defineTargetAndArrivalOrientation() {
    target = vss::Pose(35,65,0);
    return target;
}