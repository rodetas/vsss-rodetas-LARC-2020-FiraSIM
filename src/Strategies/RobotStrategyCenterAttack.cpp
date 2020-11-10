//
//Created by Samuel on 04/10/18
//
#include <Strategies/RobotStrategyCenterAttack.h>
#include <iostream>

RobotStrategyCenterAttack::RobotStrategyCenterAttack(){
    stopCenterAttacker = true;
}

vss::WheelsCommand RobotStrategyCenterAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    c = kickStrategy(c);
    if (stopCenterAttacker) {
        c = stopStrategy(c);
    }
    return c;
}

vss::Pose RobotStrategyCenterAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    target.x = (vss::MAX_COORDINATE_X  - 20) * 0.4;
    target.y = vss::MAX_COORDINATE_Y * 0.5;

    stopCenterAttacker = true;

    if (state.ball.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25) {
        if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.5) {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.25;
            target.y = vss::MAX_COORDINATE_Y * 0.70;
            target.angle = 0;
        } else {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.25;
            target.y = vss::MAX_COORDINATE_Y * 0.30;
            target.angle = 0;
        }
        }
    
    if (state.ball.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25) {
        //de cima pra baixo
        if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
            state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 && state.ball.projection.y > state.ball.position.y) {
            if( robot.position.y - state.ball.position.y >= 5){
                target.x = state.ball.projection.x;
                target.y = (state.ball.projection.y + 2);
            }else{
                target.x = state.ball.position.x;
                target.y = state.ball.position.y;
            }

            vss::Point targetPoint(target.x, target.y);
            vss::Point targetCross(centerGoal.x,centerGoal.y);
            target.angle = Math::arrivalAngle(targetPoint, targetCross);
            target.x = state.ball.position.x - 10;
            target.y = state.ball.position.y - 2;
   
            stopCenterAttacker = false;
            
        //de baixo pra cima
        } else if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 &&
                   state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
                   state.ball.projection.y < state.ball.position.y) {
            if(state.ball.position.y - robot.position.y >= 5){
                target.x = state.ball.projection.x;
                target.y = (state.ball.projection.y - 2);
            }else{
                target.x = 0;
                target.y = vss::MAX_COORDINATE_Y/2 + 5;
            }


            vss::Point targetPoint(target.x, target.y);
            vss::Point targetCross2(centerGoal.x,centerGoal.y);
            target.angle = Math::arrivalAngle(targetPoint, targetCross2);
            target.x = state.ball.position.x - 10;
            target.y = state.ball.position.y + 2;
   

            stopCenterAttacker = false;
        }
    }
    int speed = 1;
    robot.setRobotSpeed(speed);
    return target;

}


float RobotStrategyCenterAttack::applyUnivectorField(vss::Pose target) {
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