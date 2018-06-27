//
// Created by manoel on 18/04/18.
//

#include "Strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() = default;

vss::WheelsCommand RobotStrategyAttack::specificStrategy(vss::WheelsCommand c) {
    c = kickStrategy(c);
    c = cornerStrategy(c);

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

vss::Pose RobotStrategyAttack::defineTargetAndArrivalOrientation(){
    vss::Pose target;
    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
    //Orientação pro gol
    float numerator = abs(target.y - centerGoal.y);
    float denominator = abs(target.x - centerGoal.x);
    float tg = (numerator/denominator);
    float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
    float deltaY = tg * deltaX;
    if(target.y < centerGoal.y){
        arrivalOrientation.x = target.x - deltaX;
        arrivalOrientation.y = target.y + deltaY;
    }else{
        arrivalOrientation.x = target.x - deltaX;
        arrivalOrientation.y = target.y - deltaY;
    }

    //Orientação pro canto da parede
    if(target.y < 13){
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y - 7;
    }
    if(target.y > 115){
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y + 7;
    }
    if(target.x > 140 && target.y < 48){
        arrivalOrientation.x = target.x;
        arrivalOrientation.y = target.y - 10;
    }
    if(target.x > 140 && target.y > 86){
        arrivalOrientation.x = target.x;
        arrivalOrientation.y = target.y + 10;
    }


    double angleRobotGoal = Math::angulation(robot.position, centerGoal);

    if(angleRobotGoal < 45.0 && angleRobotGoal > -45.0 && (robot.cosFrom(centerGoal) < -0.8 || robot.cosFrom(centerGoal) > 0.8) &&
       (robot.cosFrom(state.ball.position) < -0.8 || robot.cosFrom(state.ball.getPosition()) > 0.8) &&
       robot.position.x > state.ball.position.x && robot.distanceFrom(state.ball.position) < (8)){

        target.x = centerGoal.x;
        target.y = centerGoal.y;

        //Orientação para um pouco além do gol para a reta funcionar
        float numerator = abs(target.y - centerGoal.y);
        float denominator = abs(target.x - centerGoal.x -5);
        float tg = (numerator/denominator);
        float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
        float deltaY = tg * deltaX;
        if(target.y < centerGoal.y){
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y + deltaY;
        }else{
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y - deltaY;
        }
    }

    int halfGoal1 = vss::MAX_COORDINATE_Y/2 + Config::goalSize.y * 0.85;
    int halfGoal2 = vss::MAX_COORDINATE_Y/2 - Config::goalSize.y * 0.85;

    // caso a bola esteja entrando na area manda o atacante para o meio do campo para evitar cometer penalti
    if(((state.ball.projection.y < halfGoal1 && state.ball.projection.y > halfGoal2 && state.ball.projection.x > vss::MAX_COORDINATE_X*0.80))){
        target = vss::Pose(vss::MAX_COORDINATE_X/2, vss::MAX_COORDINATE_Y/2, 0);
        //Orientação pro lado do gol
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y;
    }

    // verifies the limits of the destination
    if (target.y < 0) target.y = 0;
    if (target.y > vss::MAX_COORDINATE_Y) target.y = vss::MAX_COORDINATE_Y;

    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    int halfGoal1 = vss::MAX_COORDINATE_Y/2 + Config::goalSize.y * 0.85;
    int halfGoal2 = vss::MAX_COORDINATE_Y/2 - Config::goalSize.y * 0.85;

    bool flag = (state.ball.projection.y < halfGoal1 && state.ball.projection.y > halfGoal2 && state.ball.projection.x > vss::MAX_COORDINATE_X*0.80);

    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) || flag) {
        //Target na bola

        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    //Obstáculos de área do gol
    std::pair<vss::Point, vss::Point> obstacle;
    obstacle.first.x = 150;
    obstacle.first.y = 38;
    obstacle.second.x = 0;
    obstacle.second.y = 0;
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
    obstacle.first.y = 90;
    obstacles.push_back(obstacle);
    obstacle.first.x = 160;
    obstacle.first.y = 92;
    obstacles.push_back(obstacle);
    obstacle.first.x = 160;
    obstacle.first.y = 40;
    obstacles.push_back(obstacle);

    UnivectorField univectorField(2, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}
