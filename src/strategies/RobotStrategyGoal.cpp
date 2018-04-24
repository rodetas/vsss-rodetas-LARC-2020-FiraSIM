//
// Created by manoel on 23/04/18.
//

#include "strategies/RobotStrategyGoal.h"

RobotStrategyGoal::RobotStrategyGoal() = default;

Command RobotStrategyGoal::specificStrategy(Command c) {
    c = stop_strategy(c);

    return c;
}

btVector3 RobotStrategyGoal::defineTarget() {
    btVector3 goal_target;
    btVector3 ball_projection = state.ball.projection;

    // posição para seguir linha da bola
    goal_target.x = imageSize.x - 20;
    goal_target.y = ball_projection.y;

    // máximo que pode ir até a lateral da área
    if(goal_target.y > imageSize.y/2 + goalAreaSize.y/2){
        goal_target.y = imageSize.y/2 + goalAreaSize.y/2;

    } else if(goal_target.y < imageSize.y/2 - goalAreaSize.y/2){
        goal_target.y = imageSize.y/2 - goalAreaSize.y/2;
    }

    // ir na bola quando ela está dentro da area
    if (ball_projection.y > (imageSize.y/2 - goalAreaSize.y/2) &&
        ball_projection.y < (imageSize.y/2 + goalAreaSize.y/2) &&
        ball_projection.x > imageSize.x - 30){

        goal_target = ball_projection;
    }

    // quando esta agarrado manda ir para o centro do gol na tentativa de soltar
    if(strategyBase.isStoppedFor(90) && robot.distanceFrom(goal_target) > 6){
        goal_target.x = imageSize.x - 10;
        goal_target.y = imageSize.y/2;
    }

    return goal_target;
}

Command RobotStrategyGoal::stop_strategy(Command command){
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
            c = movimentation->turn_right(10, 10);
        }
    }

    return c;
}
