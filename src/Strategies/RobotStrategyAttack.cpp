//
// Created by manoel on 18/04/18.
//

#include "Strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() {

}

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

vss::Pose RobotStrategyAttack::defineTarget() {

    vss::Pose target;
    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
    double angleRobotGoal = Math::angulation(robot.position, centerGoal);

    if(angleRobotGoal < 45.0 && angleRobotGoal > -45.0 && (robot.cosFrom(centerGoal) < -0.8 || robot.cosFrom(centerGoal) > 0.8) &&
       (robot.cosFrom(state.ball.position) < -0.8 || robot.cosFrom(state.ball.getPosition()) > 0.8) &&
       robot.position.x > state.ball.position.x && robot.distanceFrom(state.ball.position) < (8)){

        target.x = centerGoal.x;
        target.y = centerGoal.y;

    }

    int halfGoal1 = vss::MAX_COORDINATE_Y/2 + Config::goalSize.y * 0.85;
    int halfGoal2 = vss::MAX_COORDINATE_Y/2 - Config::goalSize.y * 0.85;

    // caso a bola esteja entrando na area manda o atacante para o meio do campo para evitar cometer penalti
    if(((state.ball.projection.y < halfGoal1 && state.ball.projection.y > halfGoal2 && state.ball.projection.x > vss::MAX_COORDINATE_X*0.80))){
        target = vss::Pose(vss::MAX_COORDINATE_X/2, vss::MAX_COORDINATE_Y/2, 0);
    }

    // verifies the limits of the destination
    if (target.y < 0) target.y = 0;
    if (target.y > vss::MAX_COORDINATE_Y) target.y = vss::MAX_COORDINATE_Y;

    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

    vss::Point arrivalOrientation = defineArrivalOrientation(target);

    //Obstáculos roboôs
    vector<pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
            obstacles.push_back(make_pair(r.position, r.vectorSpeed));
        }
    }

    //Obstáculos de área do gol
    pair<vss::Point, vss::Point> obstacle;
    obstacle.first.x = 150;
    obstacle.first.y = 38;
    obstacle.second.x = 0;
    obstacle.second.y = 0;
    obstacles.push_back(obstacle);
    obstacle.first.y = 50;
    obstacles.push_back(obstacle);
    obstacle.first.y = 60;
    obstacles.push_back(obstacle);
    obstacle.first.y = 70;
    obstacles.push_back(obstacle);
    obstacle.first.y = 80;
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

vss::Point RobotStrategyAttack::defineArrivalOrientation(vss::Pose target) {
    vss::Point goal(0, 75);
    vss::Point arrivalOrientation;

    if((target.x == state.ball.position.x) && (target.y == state.ball.position.y)){

        if(target.y < 13){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y - 7;
            return arrivalOrientation;
        }

        if(target.y > 115){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y + 7;
            return arrivalOrientation;
        }

        if(target.x > 140 && target.y < 48){
            arrivalOrientation.x = target.x;
            arrivalOrientation.y = target.y - 10;
            return arrivalOrientation;
        }

        if(target.x > 140 && target.y > 86){
            arrivalOrientation.x = target.x;
            arrivalOrientation.y = target.y + 10;
            return arrivalOrientation;
        }


        float numerator = abs(target.y - goal.y);
        float denominator = abs(target.x - goal.x);
        float tg = (numerator/denominator);
        float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
        float deltaY = tg * deltaX;

        if(target.y < goal.y){
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y + deltaY;
        }else{
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y - deltaY;
        }
        return arrivalOrientation;
    } else{
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y;
        return arrivalOrientation;
    }
}
