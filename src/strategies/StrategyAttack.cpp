#include "StrategyAttack.h"

StrategyAttack::StrategyAttack() : StrategyBase(){
	name = "attack";
}

Command StrategyAttack::strategy(Robot robot, Command command){
	Command c = command;
	c = kick_strategy(c);
	c = corner_strategy(c);

	if (robot.is_parallel_goal(image_size)){

		int halfGoal1 = image_size.y/2 + (goal_size.y/2);
		int halfGoal2 = image_size.y/2 - (goal_size.y/2);

		if ( robot.distance_from(state.ball.get_position()) < (6) && 
		    !(robot.x() < image_size.x * 0.1 && robot.y() < halfGoal1) &&
		    !(robot.x() < image_size.x * 0.1 && robot.y() > halfGoal2) ){
			
			if (robot.y() < state.ball.y()) {
				c = movimentation.turn_right(255, 255);
			} else {
				c = movimentation.turn_left(255, 255);
			}
		}
	}

	return c;
}

btVector3 StrategyAttack::define_target(Robot robot){

	btVector3 target = state.ball.get_position();

	/* btVector3 centerGoal = btVector3(0, image_size.y/2);
	float angle_robot_goal = angulation(centerGoal, robot.get_position());

	if(angle_robot_goal < 45.0 && angle_robot_goal > -45.0 && (robot.cos_from(centerGoal) < -0.8 || robot.cos_from(centerGoal) > 0.8) && 
		(robot.cos_from(state.ball.get_position()) < -0.8 || robot.cos_from(state.ball.get_position()) > 0.8) &&
		robot.x() > state.ball.x() && robot.distance_from(state.ball.get_position()) < (8)){

		target = centerGoal;
	} 

	if (target.y < 0) target.y = 0;
	if (target.y > image_size.y) target.y = image_size.y; 
 */
	return target;
}

Command StrategyAttack::kick_strategy(Command _command){
	Command c = _command;

	Point centerGoal = btVector3(0, image_size.y/2);
	float angle_robot_goal = angulation(centerGoal, robot.get_position());

	if(angle_robot_goal < 45.0 && angle_robot_goal > -45.0 && (robot.cos_from(centerGoal) < -0.8 || robot.cos_from(centerGoal) > 0.8) && 
		(robot.cos_from(state.ball.get_position()) < -0.8 || robot.cos_from(state.ball.get_position()) > 0.8) &&
		robot.x() > state.ball.x() && robot.distance_from(state.ball.get_position()) < (8)){

		c.left  *= 1.5;
		c.right *= 1.5;
	} 

	return c;
}