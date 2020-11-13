//
// Created by manoel on 18/04/18.
//

#include "Strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() {
    stopAttacker = false;
}

vss::WheelsCommand RobotStrategyAttack::specificStrategy(vss::WheelsCommand c) {
   c = kickStrategy(c);
    c = cornerStrategy(c);

    if (stopAttacker) {
        c = stopStrategy(c);
    }

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

vss::Pose RobotStrategyAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal1 = vss::Point(0, vss::MAX_COORDINATE_Y / 2);
    vss::Point centerGoal2 = vss::Point(0, vss::MAX_COORDINATE_Y / 2);
    vss::Point targetPoint;

    //Posiciona o atacante no meio do campo para ele nao interferir na defesa
    if (state.ball.projection.x > (vss::MAX_COORDINATE_X  - 20) * 0.6 && (state.ball.position.x > robot.position.x)) {
        if (state.ball.projection.y < vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose((vss::MAX_COORDINATE_X  - 20) * 0.55, vss::MAX_COORDINATE_Y * 0.2, 0);
            stopAttacker = true;
        } else {
            target = vss::Pose((vss::MAX_COORDINATE_X  - 20) * 0.55, vss::MAX_COORDINATE_Y * 0.8, 0);
            stopAttacker = true;
        }
    } else {
        stopAttacker = false;

        if(state.ball.linearSpeed ==0)
        {   target.x = state.ball.position.x;
           target.y = state.ball.position.y;
        }
        else{
            target.x = state.ball.projection.x;
            target.y = state.ball.projection.y;
        }
        if(target.y < (target.y < vss::MAX_COORDINATE_Y * 0.5) )
            target.angle = Math::arrivalAngle(target, centerGoal1);
        else target.angle = Math::arrivalAngle(target, centerGoal2);
        
        //Angulos para quando robô estiver na parede
        if (target.y < vss::MAX_COORDINATE_Y * 0.25) {
            target.angle = 0;
        }
        if (target.y > vss::MAX_COORDINATE_Y * 0.75) {
            target.angle = 0;
        }
        if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y < vss::MAX_COORDINATE_Y * 0.5)) {
        target.angle = (3 * M_PI) / 2;
    }
    if ((target.x > (vss::MAX_COORDINATE_X  - 20) * 0.88) && (target.y > vss::MAX_COORDINATE_Y * 0.5)) {
        target.angle = M_PI_2;
    }

    }

    //target.x = state.ball.position.x;
    //target.y = state.ball.position.y;
    //target.angle = 0;
    //targetPoint.x = target.x;
    //targetPoint.y = target.y;
    
    //target.x = state.ball.projection.x;
    //target.y = state.ball.projection.y;
    //target.angle = 0;
    //speed = 2;
    //robot.setRobotSpeed(speed);
    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

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

        obstacle.first.x = 130;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }

    UnivectorField univectorField(robot);
    
    //univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        obstacles.clear();
    }

    //univectorField.setUnivectorWithoutCurves();

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

