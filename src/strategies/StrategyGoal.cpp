#include "StrategyGoal.h"

StrategyGoal::StrategyGoal() : StrategyBase() {
	name = "goal";
}

Command StrategyGoal::strategy(Robot robot, Command command){
	Command c = command;

	c = stopStrategy(c);
	
	return c;
}

void StrategyGoal::defineCommand(Command _command){
	command = _command;
}

void StrategyGoal::defineTarget(Robot robot){

	Point ballProjection = state.ball.getProjection();

	target.x = image_size.x * (0.95);
	target.y = image_size.y/2 - (image_size.y/2 - ballProjection.y)/2;
}

Command StrategyGoal::stopStrategy(Command command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = command;
    float maxDistance = robot.getRadius() * (3);
	float distanceTarget = robot.distanceFrom(target);

/*	REVER VELOCIDADE 
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = robot.getRadius() * (6);
	}
 */
	if(distanceTarget < maxDistance){
		c.left  = command.left  * (distanceTarget/maxDistance);
		c.right = command.right * (distanceTarget/maxDistance);
	}

	if(distanceTarget < robot.getRadius()){

        if ((robot.yaw() > 80 && robot.yaw() < 120) || (robot.yaw() > 260 && robot.yaw() < 300)) {
            c = movimentation.stop();
        } else {
			c = movimentation.turnRight(10, 10);
        }
    }

    return c;
}