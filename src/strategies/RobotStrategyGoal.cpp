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
    if(goalTarget.y > Config::fieldSize.y/2 + Config::goalAreaSize.y/2){
        goalTarget.y = Config::fieldSize.y/2 + Config::goalAreaSize.y/2;

    } else if(goalTarget.y < Config::fieldSize.y/2 - Config::goalAreaSize.y/2){
        goalTarget.y = Config::fieldSize.y/2 - Config::goalAreaSize.y/2;
    }

    // ir na bola quando ela está dentro da area
    if (ballProjection.y > (Config::fieldSize.y/2 - Config::goalAreaSize.y/2) &&
        ballProjection.y < (Config::fieldSize.y/2 + Config::goalAreaSize.y/2) &&
        ballProjection.x > Config::fieldSize.x - 30){

        goalTarget = ballProjection;
    }

    // quando esta agarrado manda ir para o centro do gol na tentativa de soltar
    if(strategyBase.isStoppedFor(90) && robot.distanceFrom(goalTarget) > 6){
        goalTarget.x = Config::fieldSize.x - 10;
        goalTarget.y = Config::fieldSize.y/2;

    }

    return goalTarget;
}

Command RobotStrategyGoal::stopStrategy(Command command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

/*	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
 */
    if(distanceTarget < maxDistance){
        c.left  = command.left  * (distanceTarget/maxDistance);
        c.right = command.right * (distanceTarget/maxDistance);
    }

    if(distanceTarget < (4)){

        if ((robot.angle > 80 && robot.angle < 120) || (robot.angle > 260 && robot.angle < 300)) {
            c = movimentation->stop();
        } else {
            c = movimentation->turnRight(10, 10);
        }
    }

    return c;
}
