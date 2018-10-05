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

    //Muda o target para a projeção para tentar melhorar o cruzamento
    /*if(state.ball.position.x < 30 && robot.position.x - state.ball.position.x > 4){
        target.x = state.ball.projection.x;
        target.y = state.ball.projection.y;
    }
    else if((state.ball.position.x < 30 && robot.position.x - state.ball.position.x < 3)){
        target.x = state.ball.position.x;
        target.y = state.ball.position.y;
    }
    else {
        target.x = state.ball.position.x;
        target.y = state.ball.position.y;
    }*/

    target.x = state.ball.position.x;
    target.y = state.ball.position.y;

    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
    vss::Point orientationPoint;
    //Define orientação de chegada para os cantos do gol dependendo do lado de ataque e da proximidade do gol
    if(state.ball.position.x < 85 && state.ball.position.x > 25){
        if(state.ball.position.y < 45){
            orientationPoint.x = 0;
            orientationPoint.y = 85;
        }else if(state.ball.position.y > 85){
            orientationPoint.x = 0;
            orientationPoint.y = 45 ;
        }else{
            orientationPoint.x = centerGoal.x;
            orientationPoint.y = centerGoal.y;
        }
    }else{
        orientationPoint.x = centerGoal.x;
        orientationPoint.y = centerGoal.y;
    }

    //Orientação pro gol na linha da bola
    if(state.ball.position.y > 50 && state.ball.position.y < 80 && state.ball.position.x < 65){
        orientationPoint.x = 0;
        orientationPoint.y = state.ball.position.y;
    }

    //Orientação pro gol
    float numerator = abs(target.y - orientationPoint.y);
    float denominator = abs(target.x - orientationPoint.x);
    float tg = (numerator/denominator);
    float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
    float deltaY = tg * deltaX;
    if(target.y < orientationPoint.y){
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
        if(target.x < 20){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y;
        }
    }
    if(target.y > 115){
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y + 7;
        if(target.x < 20){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y;
        }
    }
    if(target.x > 150 && target.y < 48){
        arrivalOrientation.x = target.x;
        arrivalOrientation.y = target.y - 10;
    }
    if(target.x > 150 && target.y > 86){
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
        if(target.y < orientationPoint.y){
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
        target = vss::Pose(vss::MAX_COORDINATE_X/2 + 25, vss::MAX_COORDINATE_Y/2, 0);
        //Orientação pro lado do gol
        arrivalOrientation.x = target.x;
        arrivalOrientation.y = target.y;
    }

    // verifies the limits of the destination
    if (target.y < 0) target.y = 0;
    if (target.y > vss::MAX_COORDINATE_Y) target.y = vss::MAX_COORDINATE_Y;

    target.angle = 0;

    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    //Se o target for a bola ou sua projeção e o robo estiver longe, desvia de todos
    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) || (target.x == state.ball.projection.x && target.y == state.ball.position.y)) {
        if(robot.distanceFrom(target) > 15){
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


    if(!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
     robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 -5) &&
     robot.position.x > vss::MAX_COORDINATE_X - 25)){

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
