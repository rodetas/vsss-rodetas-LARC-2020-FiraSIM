#include "StrategyAttack.h"

StrategyAttack::StrategyAttack() : StrategyBase(){
	name = "attack";
}

Command StrategyAttack::strategy(Robot robot, Command command){

	Command c = command;
	c = kickStrategy(c);
	c = cornerStrategy(c);

	if (robot.isParallelGoal(image_size)){

		int halfGoal1 = image_size.y/2 + (goal_size.y/2);
		int halfGoal2 = image_size.y/2 - (goal_size.y/2);

		if ( robot.distanceFrom(state.ball.getPosition()) < robot.getRadius() * 1.2 && 
		    !(robot.x() > image_size.x * 0.9 && robot.y() > halfGoal1) &&
		    !(robot.x() > image_size.x * 0.9 && robot.y() < halfGoal2) ){
			
			if (robot.y() > state.ball.y()) {
				c = movimentation.turnRight(255, 255);
			} else {
				c = movimentation.turnLeft(255, 255);
			}
		}
	}

	return c;
}

void StrategyAttack::defineCommand(Command _command){
	command = _command;
}

void StrategyAttack::defineTarget(Robot robot){

	target = state.ball.getProjection();

	btVector3 centerGoal = btVector3(image_size.x, image_size.y/2);
	float angle_robot_goal = angulation(centerGoal, robot.getPosition());

	if(angle_robot_goal < 45.0 && angle_robot_goal > -45.0 && (robot.cosFrom(centerGoal) < -0.8 || robot.cosFrom(centerGoal) > 0.8) && 
		(robot.cosFrom(state.ball.getPosition()) < -0.8 || robot.cosFrom(state.ball.getPosition()) > 0.8) &&
		robot.x() < state.ball.x() && robot.distanceFrom(state.ball.getPosition()) < robot.getRadius()*2){

		target = centerGoal;
	} 

	if (target.y < 0) target.y = 0;
	if (target.y > image_size.y) target.y = image_size.y; 
}

Command StrategyAttack::kickStrategy(Command _command){
	Command c = _command;

	Point centerGoal = btVector3(image_size.x, image_size.y/2);
	float angle_robot_goal = angulation(centerGoal, robot.getPosition());

	if(angle_robot_goal < 45.0 && angle_robot_goal > -45.0 && (robot.cosFrom(centerGoal) < -0.8 || robot.cosFrom(centerGoal) > 0.8) && 
		(robot.cosFrom(state.ball.getPosition()) < -0.8 || robot.cosFrom(state.ball.getPosition()) > 0.8) &&
		robot.x() < state.ball.x() && robot.distanceFrom(state.ball.getPosition()) < robot.getRadius()*2){

		c.left  *= 1.5;
		c.right *= 1.5;
	} 

	return c;
}