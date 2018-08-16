#include "Movements/Movimentation.h"


/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, vss::Pose target, float fi){

	vss::WheelsCommand command;

	double vMax = 0.6;
	double d = 0.2; // Coeficiente de ponto a frente do robô
	double r = 0.016; // Raio da roda
	double l = 0.075;// Distancia entre as rodas
	double robotAngle = Math::toDomain(Math::toRadian(robot.angle));

	double xdDot = vMax * cos(fi);
	double ydDot = vMax * sin(fi);

	double v = cos(robotAngle) * xdDot + sin(robotAngle) * ydDot;
	double w = -(sin(robotAngle)/d) * xdDot + (cos(robotAngle)/d) * ydDot;

	double wr;
	double wl;

    wr = v/r + w*(l/r);
    wl = v/r - w*(l/r);

//    if ( cos(fi - Math::toRadian(robot.angle)) > 0){
//        wr = v/r - w*(l/r);
//        wl = v/r + w*(l/r);
//    } else {
//        wr = v/r + w*(l/r);
//        wl = v/r - w*(l/r);
//    }


	std::cout<<"----"<<std::endl;
	std::cout<<"Fi: "<<cos(fi)<<std::endl;
	std::cout<<"Theta: "<<sin(fi)<<std::endl;
	std::cout<<"v: "<<v<<std::endl;
	std::cout<<"w: "<<w<<std::endl;
	std::cout<<"wr: "<<wr<<std::endl;
	std::cout<<"wl: "<<wl<<std::endl;
	//1.6 converte de rad/s para cm/s
	command = checkMaximumSpeedWheel( vss::WheelsCommand(wr, wl));

	return command;
}

vss::WheelsCommand Movimentation::checkMaximumSpeedWheel(const vss::WheelsCommand& speed){
	vss::WheelsCommand command(speed);

	int maximumSpeed = 80;

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