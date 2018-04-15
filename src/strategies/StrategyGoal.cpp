#include <StrategyGoal.h>

StrategyGoal::StrategyGoal() : StrategyBase() {
	name = "goal";
}

Command StrategyGoal::strategy(Robot robot, Command command){
	Command c = command;

	c = stop_strategy(c);
	
	return c;
}

btVector3 StrategyGoal::define_target(Robot robot){

	Point goal_target = Point(0,0);
	Point ball_projection = state.ball.get_projection();

	// posição para seguir linha da bola
	goal_target.x = image_size.x - 20;
	goal_target.y = ball_projection.y;

	// máximo que pode ir até a lateral da área
	if(goal_target.y > image_size.y/2 + goal_area_size.y/2){
		goal_target.y = image_size.y/2 + goal_area_size.y/2;

	} else if(goal_target.y < image_size.y/2 - goal_area_size.y/2){
		goal_target.y = image_size.y/2 - goal_area_size.y/2;
	}

	// ir na bola quando ela está dentro da area
	if (ball_projection.y > (image_size.y/2 - goal_area_size.y/2) &&
		ball_projection.y < (image_size.y/2 + goal_area_size.y/2) && 
		ball_projection.x > image_size.x - 30){

		goal_target = ball_projection;
	}

	// quando esta agarrado manda ir para o centro do gol na tentativa de soltar
	if(robot.is_stopped_for(90) && robot.distance_from(goal_target) > 6){
		goal_target.x = image_size.x - 10;
		goal_target.y = image_size.y/2;
    }

	return goal_target;
}

Command StrategyGoal::stop_strategy(Command command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = command;
    float maxDistance = (12); // 12 cm
	float distanceTarget = robot.distance_from(robot.get_target());

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

        if ((robot.yaw() > 80 && robot.yaw() < 120) || (robot.yaw() > 260 && robot.yaw() < 300)) {
            c = movimentation->stop();
        } else {
			c = movimentation->turn_right(10, 10);
        }
    }
    return c;
}