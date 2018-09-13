//
// Created by manoel on 12/09/18.
//

#include <Positioning/GoalKeeperCenterPositioning.h>

vss::WheelsCommand GoalKeepCenterPositioning::specificStrategy(vss::WheelsCommand c) {
    return c;
}

vss::Pose GoalKeepCenterPositioning::defineTargetAndArrivalOrientation() {
    target = vss::Pose(150, 65, 90);

    return target;
}