#include "Movements/Movimentation.h"


Movimentation::Movimentation() = default;

/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, float fi, vss::Point target, RobotSpeed speed, MindSet mindSet){

	vss::WheelsCommand command;

	double realSpeedMax = 80;
	double controllerSpeedMax = 0.8;

	if(speed == RobotSpeed::SLOW) controllerSpeedMax = 0.4;
	if(speed == RobotSpeed::FAST) controllerSpeedMax = 0.6;
	if(speed == RobotSpeed::SUPERFAST) controllerSpeedMax = 1.2;

    double step;
    if(mindSet == MindSet::AttackerStrategy || mindSet == MindSet::SingleAttackerStrategy){
        step = 0.6;

    } else if(mindSet == MindSet::GoalKeeperStrategy){
		step = 0.6;

    } else if(mindSet == MindSet::DefenderStrategyRight || mindSet == MindSet::DefenderStrategyLeft || mindSet == MindSet::DefenderStrategy){
		step = 0.6;

    } else {
        step = 0.6;
    }

	double d;
	if(Config::realEnvironment){
		d = 0.4;
		if(mindSet == MindSet::DefenderStrategy) d = 0.5;

	} else {
        d = 0.1;
	}

    double r = 0.016; // Raio da roda
	double l = 0.075; // Distancia entre as rodas
	double robotAngle = Math::toDomain(Math::toRadian(robot.angle));

	double xdDot = controllerSpeedMax * cos(fi);
	double ydDot = controllerSpeedMax * sin(fi);

	double v = cos(robotAngle) * xdDot + sin(robotAngle) * ydDot;
	double w = -(sin(robotAngle) / d) * xdDot + (cos(robotAngle) / d) * ydDot;

	double wr = v / r + w * (l / r);
	double wl = v / r - w * (l / r);

	// conversão rad/s para cm/s
	wr = wr * r * 100;
	wl = wl * r * 100;

	if (wr > 0 && wl > 0) {
		double aux = wr;
		wr = wl;
		wl = aux;
	}

	double linearSpeed = std::abs((wr + wl) / 2);

    if (robot.linearSpeed < 40) {
        double k = 1 - (step * std::abs(linearSpeed - robot.linearSpeed) / realSpeedMax);
        wr *= k;
        wl *= k;
    }

	command = checkMaximumSpeedWheel( vss::WheelsCommand(wl, wr), realSpeedMax);

	return command;
}

vss::WheelsCommand Movimentation::checkMaximumSpeedWheel(const vss::WheelsCommand& speed, int maximumSpeed){
	vss::WheelsCommand command(speed);

	if(speed.leftVel  > maximumSpeed) command.leftVel  = maximumSpeed;
	if(speed.rightVel > maximumSpeed) command.rightVel = maximumSpeed;

	if(speed.leftVel  < -maximumSpeed) command.leftVel  = -maximumSpeed;
	if(speed.rightVel < -maximumSpeed) command.rightVel = -maximumSpeed;

	return command;
}

vss::WheelsCommand Movimentation::turnLeft(int speed1, int speed2){
	vss::WheelsCommand command(-speed1, speed2);
	return command;
}

vss::WheelsCommand Movimentation::turnRight(int speed1, int speed2){
	vss::WheelsCommand command(speed1, -speed2);
	return command;
}

vss::WheelsCommand Movimentation::stop(){
	vss::WheelsCommand command(0, 0);
	return command;
}
