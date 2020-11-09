//
//Created by Samuel on 28/09/18
//
#include <Strategies/RobotStrategyAttackDefense.h>
#include <iostream>

RobotStrategyAttackDefense::RobotStrategyAttackDefense(){
    stopAttackerDefense = false;
}

vss::WheelsCommand RobotStrategyAttackDefense::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);

    if (stopAttackerDefense) {
        c = stopStrategy(c);
    }

    return c;
}

vss::Pose RobotStrategyAttackDefense::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    //Posiciona o atacante defensor no meio do campo para ele nao interferir no ataque
    if (state.ball.projection.x < (vss::MAX_COORDINATE_X  - 20) * 0.6) {
        if (state.ball.projection.y > vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose((vss::MAX_COORDINATE_X  - 20) * 0.55, vss::MAX_COORDINATE_Y * 0.8, 0);
            stopAttackerDefense = true;
        } else {
            target = vss::Pose((vss::MAX_COORDINATE_X  - 20) * 0.55, vss::MAX_COORDINATE_Y * 0.2, 0);
            stopAttackerDefense = true;
        }
    } else {
        stopAttackerDefense = false;

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
        if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y < vss::MAX_COORDINATE_Y * 0.37)) {
            target.angle = (3 * M_PI) / 2;
        }
        if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y > vss::MAX_COORDINATE_Y * 0.66)) {
            target.angle = M_PI_2;
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

    //Obstáculos de área do gol
    std::pair<vss::Point, vss::Point> obstacle;

    obstacle.second.x = 0;
    obstacle.second.y = 0;

    if (!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
          robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 5) &&
          robot.position.x > (vss::MAX_COORDINATE_X  - 20) - 25)) {

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

    UnivectorField univectorField(robot);

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        univectorField.setUnivectorWithoutCurves();
        obstacles.clear();
    }

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}