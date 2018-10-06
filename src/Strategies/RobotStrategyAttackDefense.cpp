//
//Created by Samuel on 28/09/18
//
#include <Strategies/RobotStrategyAttackDefense.h>
#include <iostream>

RobotStrategyAttackDefense::RobotStrategyAttackDefense() = default;

vss::WheelsCommand RobotStrategyAttackDefense::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyAttackDefense::defineTarget() {
    vss::Pose target;
    target.x = vss::MAX_COORDINATE_X * 0.5;
    target.y = vss::MAX_COORDINATE_Y * 0.5;
    if (state.ball.projection.x > vss::MAX_COORDINATE_X * 0.7) {
        if (state.ball.projection.y > vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.55, vss::MAX_COORDINATE_Y * 0.8, 0);

        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.55, vss::MAX_COORDINATE_Y * 0.2, 0);
        }
    }

    return target;

}


float RobotStrategyAttackDefense::applyUnivectorField(vss::Pose target) {
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }
    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}