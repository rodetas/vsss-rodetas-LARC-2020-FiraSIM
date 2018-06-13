//
// Created by manoel on 23/04/18.
//

#include "strategies/RobotStrategyGoal.h"

RobotStrategyGoal::RobotStrategyGoal() = default;

Command RobotStrategyGoal::specificStrategy(Command c) {
    c = stopStrategy(c);

    return c;
}

btVector3 RobotStrategyGoal::defineTarget() {
    btVector3 goalTarget;
    btVector3 ballProjection = state.ball.projection;

    // posição para seguir linha da bola
    goalTarget.x = Config::fieldSize.x - 20;
    goalTarget.y = ballProjection.y;

    // máximo que pode ir até a lateral da área
    if (goalTarget.y > Config::fieldSize.y / 2 + Config::goalAreaSize.y / 2) {
        goalTarget.y = Config::fieldSize.y / 2 + Config::goalAreaSize.y / 2;

    } else if (goalTarget.y < Config::fieldSize.y / 2 - Config::goalAreaSize.y / 2) {
        goalTarget.y = Config::fieldSize.y / 2 - Config::goalAreaSize.y / 2;
    }

    // ir na bola quando ela está dentro da area
    if (ballProjection.y > (Config::fieldSize.y / 2 - Config::goalAreaSize.y / 2) &&
        ballProjection.y < (Config::fieldSize.y / 2 + Config::goalAreaSize.y / 2) &&
        ballProjection.x > Config::fieldSize.x - 30) {

        goalTarget = ballProjection;
    }

    // quando esta agarrado manda ir para o centro do gol na tentativa de soltar
    if (strategyBase.isStoppedFor(90) && robot.distanceFrom(goalTarget) > 6) {
        goalTarget.x = Config::fieldSize.x - 10;
        goalTarget.y = Config::fieldSize.y / 2;

    }

    return goalTarget;
}

float RobotStrategyGoal::applyUnivectorField(btVector3 target) {
    /* Se o target for a bola e se a bola estiver atrás do goleiro indo pro gol, definir angulo de chegada
     * para que o robô chega até a bola por trás evitando gol contra e a levando para fora do gol*/

    float n = 0;
    btVector3 arrivalOrientation = defineArrivalOrientation(target);

    if((target.x == state.ball.projection.x) && (target.y == state.ball.projection.y)){
        if(target.x > robot.position.x - 3){
            n = 1.6;
        }
    }
    vector<pair<btVector3, btVector3>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
            obstacles.push_back(make_pair(r.position, r.vectorSpeed));
        }
    }

    //Obstáculos de canto de gol
    pair<btVector3, btVector3> obstacle;
    obstacle.first.x = 163;
    obstacle.first.y = 40;
    obstacle.second.x = 0;
    obstacle.second.y = 0;
    obstacles.push_back(obstacle);
    obstacle.first.y = 88;
    obstacles.push_back(obstacle);

    UnivectorField univectorField(n, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}

Command RobotStrategyGoal::stopStrategy(Command command) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

/*	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
 */
    if (distanceTarget < maxDistance) {
        c.left = command.left * (distanceTarget / maxDistance);
        c.right = command.right * (distanceTarget / maxDistance);
    }

    if (distanceTarget < (4)) {

        if ((robot.angle > 80 && robot.angle < 120) || (robot.angle > 260 && robot.angle < 300)) {
            c = movimentation->stop();
        } else {
            c = movimentation->turnRight(10, 10);
        }
    }

    return c;
}

btVector3 RobotStrategyGoal::defineArrivalOrientation(btVector3 target) {
    btVector3 arrivalOrientation;

    if(robot.position.y < target.y){
        arrivalOrientation.x = target.x - 8;
        arrivalOrientation.y = target.y + 10;
    }else{
        arrivalOrientation.x = target.x - 8;
        arrivalOrientation.y = target.y - 10;
    }
    return arrivalOrientation;
}
