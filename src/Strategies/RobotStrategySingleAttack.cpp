//
// Created by paulo on 30/10/18.
//

#include "Strategies/RobotStrategySingleAttack.h"

RobotStrategySingleAttack::RobotStrategySingleAttack() = default;

vss::WheelsCommand RobotStrategySingleAttack::specificStrategy(vss::WheelsCommand c) {
    c = kickStrategy(c);
//    c = cornerStrategy(c);

    if (strategyBase.isParallelToGoal()) {

        int halfGoal1 = vss::MAX_COORDINATE_Y / 2 + (Config::goalSize.y / 2);
        int halfGoal2 = vss::MAX_COORDINATE_Y / 2 - (Config::goalSize.y / 2);

        if (robot.distanceFrom(state.ball.position) < 7 &&
            robot.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25 && robot.position.y > halfGoal2 &&
            robot.position.y < halfGoal1) {

            if (robot.position.y < state.ball.position.y) {
                c = movimentation.turnRight(60, 60);
            } else {
                c = movimentation.turnLeft(60, 60);
            }
        }
    }

    return c;
}

vss::Pose RobotStrategySingleAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    vss::Point targetPoint(target.x, target.y);

    target.angle = Math::arrivalAngle(targetPoint, centerGoal);

    //Angulos para quando robô estiver na parede
    if (target.y < vss::MAX_COORDINATE_Y * 0.1) {
        target.angle = 0;
    }
    if (target.y > vss::MAX_COORDINATE_Y * 0.88) {
        target.angle = 0;
    }
    if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y < vss::MAX_COORDINATE_Y * 0.5)) {
        target.angle = (3 * M_PI) / 2;
    }
    if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y > vss::MAX_COORDINATE_Y * 0.5)) {
        target.angle = M_PI_2;
    }

    //target.x = 140;
    //target.y = 115;

    //target.angle = 0;

    return target;
}

float RobotStrategySingleAttack::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    UnivectorField univectorField(robot);
    path = univectorField.drawPath(robot, target, obstacles);

    if (univectorField.offTheField) {
        univectorField.setUnivectorWithoutCurves();
        obstacles.clear();
    }

    univectorField.setUnivectorWithoutCurves();
    path = univectorField.drawPath(robot, target, obstacles);

//    std::cout << "INICIO PATH" << std::endl;
//    for (auto i : path.points) {
//        std::cout << i << std::endl;
//    }
//    std::cout << "FIM PATH" << std::endl << std::endl << std::endl;

    return univectorField.defineFi(robot, target, obstacles);
}