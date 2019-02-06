#include "Movements/Movimentation.h"


Movimentation::Movimentation() = default;

/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, float fi, float lastFi, vss::Point lastPosition, vss::Point target, RobotSpeed speed, MindSet mindSet){

	double sampleTime = 0.01666;

    vss::WheelsCommand command;

	double realSpeedMax = 100;
	double vMax = 1;

    double r = 0.016; // Raio da roda
    double l = 0.075; // Distancia entre as rodas

    //double kw = 3;
    double robotAngle = Math::toDomain(Math::toRadian(robot.angle));
    double errorAngle = Math::toDomain(robotAngle - fi);

    vss::Point nextPosition;
    nextPosition.x = robot.position.x + cos(robotAngle)*robot.linearSpeed*sampleTime;
    nextPosition.y = robot.position.y + sin(robotAngle)*robot.linearSpeed*sampleTime;

    double d_fiy_x = (sin(fi) - sin(lastFi)) / (nextPosition.x - robot.position.x);
    double d_fix_y = (cos(fi) - cos(lastFi)) / (nextPosition.y - robot.position.y);

    double d_fiy_y = (sin(fi) - sin(lastFi)) / (nextPosition.y - robot.position.y);
    double d_fix_x = (cos(fi) - cos(lastFi)) / (nextPosition.x - robot.position.x);

    if (isnan(d_fiy_x)) {
        d_fiy_x = 0;
    }

    if (isnan(d_fix_y)) {
        d_fix_y = 0;
    }

    if (isnan(d_fiy_y)) {
        d_fiy_y = 0;
    }

    if (isnan(d_fix_x)) {
        d_fix_x = 0;
    }

    double value = 100;
    if ( d_fiy_x > value ) {
        d_fiy_x = value;
    }

    if ( d_fiy_x < -value ) {
        d_fiy_x = -value;
    }


    if ( d_fix_y > value ) {
        d_fix_y = value;
    }

    if ( d_fix_y < -value ) {
        d_fix_y = -value;
    }

    if ( d_fiy_y > value ) {
        d_fiy_y = value;
    }

    if ( d_fiy_y < -value ) {
        d_fiy_y = -value;
    }


    if ( d_fix_x > value ) {
        d_fix_x = value;
    }

    if ( d_fix_x < -value ) {
        d_fix_x = -value;
    }

    double v = -vMax;

    double kp = 15;
    double w = v*cos(errorAngle)*(d_fiy_x - d_fix_y) - v*sin(errorAngle)*(d_fix_x + d_fiy_y) + kp*sin(errorAngle);
//	if (robot.distanceFrom(target) > 30) {
//
//	} else {
//		v = (1 - 0.75 * abs(sin(errorAngle))) * vMax;
//	}
//
//    double w;
//    if (errorAngle < 0) {
//		w = (d_fi_x * cos(robotAngle) + d_fi_y * sin(robotAngle)) * v - kw * (-1) * sqrt(abs(errorAngle));
//	} else {
//		w = (d_fi_x * cos(robotAngle) + d_fi_y * sin(robotAngle)) * v - kw * sqrt(abs(errorAngle));
//	}

	double wr = v / r - w * (l / r);
	double wl = v / r + w * (l / r);

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
