//
// Created by manoel on 23/04/18.
//

#include "Strategies/RobotStrategyDefenderBack.h"

RobotStrategyDefenderBack::RobotStrategyDefenderBack() = default;

vss::WheelsCommand RobotStrategyDefenderBack::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    c = cornerStrategy(c);

    return c;
}

vss::Pose RobotStrategyDefenderBack::defineTargetAndArrivalOrientation() {
    vss::Pose goalTarget;
    vss::Point ballProjection = state.ball.projection;
    vss::Point ballPosition = state.ball.position;

    // posição para seguir linha da bola
    goalTarget.x = vss::MAX_COORDINATE_X - 60;
    goalTarget.y = ballProjection.y;

    // ir na bola quando ela está dentro da area
    if (robot.distanceFrom(ballProjection) < 30 and robot.position.x > ballPosition.x and ballPosition.x > vss::MAX_COORDINATE_X/2) {
        //Testar essas duas linhas comentadas ou ativadas e ver qual leva menos gols
        goalTarget.x = ballProjection.x;
        goalTarget.y = ballProjection.y;
    }

    if(robot.position.x < ballPosition.x){
        vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
        vss::Point orientationPoint;
        orientationPoint.x = centerGoal.x;
        orientationPoint.y = centerGoal.y;

        goalTarget.x = ballProjection.x;
        goalTarget.y = ballProjection.y;

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
    }

    if (robot.position.y < goalTarget.y) {
        arrivalOrientation.x = goalTarget.x - 8;
        arrivalOrientation.y = goalTarget.y + 10;
    } else {
        arrivalOrientation.x = goalTarget.x - 8;
        arrivalOrientation.y = goalTarget.y - 10;
    }

    return goalTarget;
}

float RobotStrategyDefenderBack::applyUnivectorField(vss::Pose target) {
    /* Se o target for a bola e se a bola estiver atrás do goleiro indo pro gol, definir angulo de chegada
     * para que o robô chega até a bola por trás evitando gol contra e a levando para fora do gol*/

    //n = 0 faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    float n = 0;
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    if (((target.x == state.ball.position.x) && (target.y == state.ball.position.y)) || ((target.x == state.ball.projection.x) && (target.y == state.ball.projection.y))) {
        if (target.x > robot.position.x) {
            n = 1.5;
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

    UnivectorField univectorField(n, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}

vss::WheelsCommand RobotStrategyDefenderBack::stopStrategy(vss::WheelsCommand command) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    vss::WheelsCommand c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

/*	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
 */
    if (distanceTarget < maxDistance) {
        c.leftVel = command.leftVel * (distanceTarget / maxDistance);
        c.rightVel = command.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < (4)) {

        if ((robot.angle > 80 && robot.angle < 120) || (robot.angle > 260 && robot.angle < 300)) {
            c = movimentation.stop();
        } else {
            c = movimentation.turnRight(10, 10);
        }
    }

    return c;
}