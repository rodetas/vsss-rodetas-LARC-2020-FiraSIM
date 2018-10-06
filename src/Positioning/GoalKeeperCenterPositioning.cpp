//
// Created by manoel on 12/09/18.
//

#include <Positioning/GoalKeeperCenterPositioning.h>

vss::WheelsCommand GoalKeepCenterPositioning::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c, vss::Point(robot.position.x, robot.position.y + 30));

    return c;
}

vss::Pose GoalKeepCenterPositioning::defineTarget() {
    // o robo vai ser preciso o suficiente para parar 90 graus no meio do gol sozinho?
    target = vss::Pose(150, 65, M_PI_2);

    return target;
}