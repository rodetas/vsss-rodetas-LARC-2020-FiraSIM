//
//Created by Samuel on 28/09/18
//
#include <Strategies/RobotStrategySideAttack.h>
#include <iostream>

RobotStrategySideAttack::RobotStrategySideAttack(){
    stopSideAttacker = false;
}

vss::WheelsCommand RobotStrategySideAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);

    if (stopSideAttacker) {
        c = stopStrategy(c);
    }

    return c;
}

vss::Pose RobotStrategySideAttack::defineTarget() {
    vss::Pose target;

    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    stopSideAttacker = false;

    //std::cout<<"posição x: "<<target.x<<" posição y: "<<target.y<<"\n";
    if (state.ball.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25) {
        if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
            state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 && state.ball.projection.y > state.ball.position.y) {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.2;
            target.y = vss::MAX_COORDINATE_Y * 0.2;
            target.angle = 0;

            stopSideAttacker = true;
        } else if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 &&
                   state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
                   state.ball.projection.y < state.ball.position.y) {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.2;
            target.y = vss::MAX_COORDINATE_Y * 0.8;
            target.angle = 0;

            stopSideAttacker = true;
        }
    }

    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) ||
        (target.x == state.ball.position.x && target.y == state.ball.projection.y)) {

        if (target.x < (vss::MAX_COORDINATE_X  - 20) * 0.2) {
            if (target.y < vss::MAX_COORDINATE_Y * 0.5) {
                target.angle = M_PI_2;
            } else {
                target.angle = (3 * M_PI) / 2;
            }
        } else if (target.x > (vss::MAX_COORDINATE_X  - 20) * 0.8) {
            if (target.y < vss::MAX_COORDINATE_Y * 0.5) {
                target.angle = (3 * M_PI) / 2;
            } else {
                target.angle = M_PI_2;
            }
        } else if (target.y < vss::MAX_COORDINATE_Y * 0.5) {
            target.angle = (3 * M_PI) / 2 + M_PI / 4;
        } else if (target.y > vss::MAX_COORDINATE_Y * 0.5) {
            target.angle = M_PI / 2 - M_PI / 4;;
        }

        if ((target.x < (vss::MAX_COORDINATE_X  - 20) * 0.88)) {
            if (target.y < vss::MAX_COORDINATE_Y * 0.1) {
                target.angle = 0;
            } else if (target.y > vss::MAX_COORDINATE_Y * 0.88) {
                target.angle = 0;
            }
        }
    }
    int speed = 0;
    robot.setRobotSpeed(speed);

    return target;
}


float RobotStrategySideAttack::applyUnivectorField(vss::Pose target) {
    std::vector <std::pair<vss::Point, vss::Point>> obstacles;

    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    //Obstáculos de área do gol
    std::pair <vss::Point, vss::Point> obstacle;

    obstacle.second.x = 0;
    obstacle.second.y = 0;


    if (!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
          robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 5) &&
          robot.position.x > (vss::MAX_COORDINATE_X  - 20) - 25)) {

        obstacle.first.x = 132;

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

        obstacle.first.x = 140;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }

    UnivectorField univectorField(robot);
    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        obstacles.clear();
    }

    univectorField.setUnivectorWithoutCurves();

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}