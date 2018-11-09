#include "Movements/Movimentation.h"


Movimentation::Movimentation() = default;

/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, float fi, float lastFi, vss::Point lastPosition, vss::Point target, RobotSpeed speed, MindSet mindSet){

	vss::WheelsCommand command;

	double realSpeedMax = 100;
    double r = 0.016; // Raio da roda
    double l = 0.075; // Distancia entre as rodas

    double kw = 0.1;
    double robotAngle = Math::toDomain(Math::toRadian(robot.angle));
    double errorAngle = robotAngle - fi;

    double d_fi_x = (fi - lastFi) / (robot.position.x - lastPosition.x);
    double d_fi_y = (fi - lastFi) / (robot.position.y - lastPosition.y);

    double v = 1;
    double w;

    if (errorAngle < 0) {
		w = (d_fi_x * cos(robotAngle) + d_fi_y * sin(robotAngle)) * v - kw * (-1) * sqrt(abs(errorAngle));
	} else {
		w = (d_fi_x * cos(robotAngle) + d_fi_y * sin(robotAngle)) * v - kw * sqrt(abs(errorAngle));
	}

	double wr = v / r + w * (l / r);
	double wl = v / r - w * (l / r);

	// conversão rad/s para cm/s
	wr = wr * r * 100;
	wl = wl * r * 100;


//	double linearSpeed = std::abs((wr + wl) / 2);
//
//    if (robot.linearSpeed < 40) {
//        double k = 1 - (step * std::abs(linearSpeed - robot.linearSpeed) / realSpeedMax);
//        wr *= k;
//        wl *= k;
//    }

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
