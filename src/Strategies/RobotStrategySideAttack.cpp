//
//Created by Samuel on 28/09/18
//
#include <Strategies/RobotStrategySideAttack.h>
#include <iostream>

RobotStrategySideAttack::RobotStrategySideAttack() = default;

vss::WheelsCommand RobotStrategySideAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategySideAttack::defineTarget() {
    vss::Pose target;

    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    if (state.ball.position.x > vss::MAX_COORDINATE_X * 0.4) {
        if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.5 && state.ball.position.y > 10) {
            target.angle = Math::toRadian(320);
        } else if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.5 && state.ball.position.y < 120) {
            target.angle = Math::toRadian(40);
        } else {
            target.angle = 0;
        }
    }
    if (state.ball.position.x < vss::MAX_COORDINATE_X * 0.1) {
        if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.03) {
            if (state.ball.projection.y > state.ball.position.y) {
                target.angle = Math::toRadian(65);
            } else {
                target.angle = Math::toRadian(295);
            }

        }

    }
    //std::cout<<"posição x: "<<target.x<<" posição y: "<<target.y<<"\n";
    if (state.ball.position.x < vss::MAX_COORDINATE_X * 0.25) {
        if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
            state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 && state.ball.projection.y > state.ball.position.y) {
            target.x = vss::MAX_COORDINATE_X * 0.2;
            target.y = vss::MAX_COORDINATE_Y * 0.2;
        } else if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 &&
                   state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
                   state.ball.projection.y < state.ball.position.y) {
            target.x = vss::MAX_COORDINATE_X * 0.2;
            target.y = vss::MAX_COORDINATE_Y * 0.8;
        }
    }

    //vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
    //vss::Point orientationPoint;

    return target;

}


float RobotStrategySideAttack::applyUnivectorField(vss::Pose target) {
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