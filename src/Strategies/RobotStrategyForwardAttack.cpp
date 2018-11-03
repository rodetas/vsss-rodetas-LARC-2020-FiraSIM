//
//Created by Samuel on 28/09/18
//
#include <Strategies/RobotStrategyForwardAttack.h>
#include <iostream>

RobotStrategyForwardAttack::RobotStrategyForwardAttack(){
    mindSet = MindSet::ForwardAttackerStrategy;
}

vss::WheelsCommand RobotStrategyForwardAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyForwardAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);
    target.x = centerGoal.x;
    target.y = centerGoal.y;

    return target;
}


float RobotStrategyForwardAttack::applyUnivectorField(vss::Pose target) {
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
    univectorField.setUnivectorWithoutCurves();

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        obstacles.clear();
    }

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}