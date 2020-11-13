//
// Created by manoel on 23/04/18.
//

#include "Strategies/RobotStrategyGoal.h"

RobotStrategyGoal::RobotStrategyGoal(){
    stopGoalKeeper = true;
}

vss::WheelsCommand RobotStrategyGoal::specificStrategy(vss::WheelsCommand c) {
    if(stopGoalKeeper){
        c = stopStrategy(c);
    }

    return c;
}

vss::Pose RobotStrategyGoal::defineTarget() {
    vss::Pose goalTarget;
    vss::Point ballProjection = state.ball.projection;
    vss::Point ballPosition = state.ball.position;

    stopGoalKeeper = true;

    // posição para seguir linha da bola
    goalTarget.x = (vss::MAX_COORDINATE_X  - 20) - 15;
    goalTarget.y = ballProjection.y;

    if (ballPosition.x > goalTarget.x){
        goalTarget.x = ballPosition.x;
    }
    // máximo que pode ir até a lateral da área
    if (goalTarget.y > vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2) {
        goalTarget.y = vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2;

    } else if (goalTarget.y < vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y /2) {
        goalTarget.y = vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2;
    }

    // ir na bola quando ela está dentro da area
    if (ballPosition.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 8) &&
        ballPosition.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 8) &&
        ballPosition.x > vss::MAX_COORDINATE_X - 30) {

        // Testar esse target como sendo ballProjection ou ballPosition
        goalTarget.x = ballPosition.x;
        goalTarget.y = ballPosition.y;

        if (state.ball.vectorSpeed.x > 0) {
            // bola indo em direcao ao gol
            goalTarget.x = ballPosition.x;
            goalTarget.y = ballPosition.y;
        }

        stopGoalKeeper = false;
    }

    //quando esta agarrado manda ir para o centro do gol na tentativa de soltar
    if (strategyBase.isStoppedFor(6000) && robot.distanceFrom(goalTarget) > 6) {
      goalTarget.x = (vss::MAX_COORDINATE_X  - 20) - 10;
        goalTarget.y = vss::MAX_COORDINATE_Y / 2;
//
    }

    if (robot.position.y < goalTarget.y) {
        goalTarget.angle = M_PI/2 - M_PI/6;
    } else {
        goalTarget.angle = (3 * M_PI)/2 + M_PI/6;
    }
    //int speed = 1;
    //robot.setRobotSpeed(speed);

    return goalTarget;
}

float RobotStrategyGoal::applyUnivectorField(vss::Pose target) {
    /* Se o target for a bola e se a bola estiver atrás do goleiro indo pro gol, definir angulo de chegada
     * para que o robô chega até a bola por trás evitando gol contra e a levando para fora do gol*/

    UnivectorField univectorField(robot);

    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    if ((target.x == state.ball.position.x) && (target.y == state.ball.position.y)) {
        if (target.y > 40 && target.y < 88) {
            if (target.x > robot.position.x) {
                univectorField.setUnivectorWithCurves();
            }
        }
    }

    if (robot.distanceFrom(target) > 30) {
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    //Obstáculos de canto de gol
    std::pair<vss::Point, vss::Point> obstacle;
    obstacle.first.x = 167;
    obstacle.first.y = 40;
    obstacle.second.x = 0;
    obstacle.second.y = 0;
    obstacles.push_back(obstacle);
    obstacle.first.y = 88;
    obstacles.push_back(obstacle);

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        univectorField.setUnivectorWithoutCurves();
        obstacles.clear();
    }
    
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

vss::WheelsCommand RobotStrategyGoal::stopStrategy(vss::WheelsCommand command) {
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
