//
// Created by manoel on 18/04/18.
//

#include "Strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() {
    stopAttacker = false;
}

vss::WheelsCommand RobotStrategyAttack::specificStrategy(vss::WheelsCommand c) {
    c = kickStrategy(c);
//    c = cornerStrategy(c);

    if (stopAttacker) {
        c = stopStrategy(c);
    }

    if (strategyBase.isParallelToGoal()) {

        int halfGoal1 = vss::MAX_COORDINATE_Y / 2 + (Config::goalSize.y / 2);
        int halfGoal2 = vss::MAX_COORDINATE_Y / 2 - (Config::goalSize.y / 2);

        if (robot.distanceFrom(state.ball.position) < 7 &&
            robot.position.x < vss::MAX_COORDINATE_X * 0.25 && robot.position.y > halfGoal2 &&
            robot.position.y < halfGoal1) {

            if (robot.position.y < state.ball.position.y) {
                c = movimentation.turnRight(80, 80);
            } else {
                c = movimentation.turnLeft(80, 80);
            }
        }
    }

    return c;
}

vss::Pose RobotStrategyAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    vss::Point targetPoint(target.x, target.y);

    target.angle = Math::arrivalAngle(targetPoint, centerGoal);

    //Angulos para quando robô estiver na parede
    if(target.y < vss::MAX_COORDINATE_Y * 0.1){
        target.angle = 0;
    }
    if(target.y > vss::MAX_COORDINATE_Y * 0.88){
        target.angle = 0;
    }
    if ((target.x > vss::MAX_COORDINATE_X * 0.88) && (target.y < vss::MAX_COORDINATE_Y * 0.37)) {
        target.angle = (3*M_PI)/2;
    }
    if ((target.x > vss::MAX_COORDINATE_X * 0.88) && (target.y > vss::MAX_COORDINATE_Y * 0.66)) {
        target.angle = M_PI_2;
    }

    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    //Se o target for a bola ou sua projeção e o robo estiver longe, desvia de todos
    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) ||
        (target.x == state.ball.projection.x && target.y == state.ball.position.y)) {
        if (robot.distanceFrom(target) > 15) {
            //Obstáculos roboôs
            for (auto &r: state.robots) {
                if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                    obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
                }
            }
        }
    }

    //Obstáculos de área do gol
    std::pair<vss::Point, vss::Point> obstacle;

    obstacle.second.x = 0;
    obstacle.second.y = 0;


    if (!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
          robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 5) &&
          robot.position.x > vss::MAX_COORDINATE_X - 25)) {

        obstacle.first.x = 152;

        obstacle.first.y = 38;
        obstacles.push_back(obstacle);
        obstacle.first.y = 45;
        obstacles.push_back(obstacle);
        obstacle.first.y = 50;
        obstacles.push_back(obstacle);
        obstacle.first.y = 55;
        obstacles.push_back(obstacle);
        obstacle.first.y = 60;
        obstacles.push_back(obstacle);
        obstacle.first.y = 65;
        obstacles.push_back(obstacle);
        obstacle.first.y = 70;
        obstacles.push_back(obstacle);
        obstacle.first.y = 75;
        obstacles.push_back(obstacle);
        obstacle.first.y = 80;
        obstacles.push_back(obstacle);
        obstacle.first.y = 85;
        obstacles.push_back(obstacle);
        obstacle.first.y = 93;
        obstacles.push_back(obstacle);

        obstacle.first.x = 160;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }


    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}
