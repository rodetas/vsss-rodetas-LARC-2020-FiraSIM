#include "Movements/Movimentation.h"


Movimentation::Movimentation() = default;

/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, float fi, RobotSpeed speed, MindSet mindSet){

	vss::WheelsCommand command;

	double vMax = 1;

	if(speed == RobotSpeed::SLOW) vMax = 0.4;
	else if(speed == RobotSpeed::FAST) vMax = 0.6;
	else if(speed == RobotSpeed::SUPERFAST) vMax = 1.2;

	double step = 0.5; //Degrau para aceleração progressiva, quanto menor mais rápida a resposta
	if(mindSet == MindSet::GoalKeeperStrategy){
		step = 0.5;
	}
	if(mindSet == MindSet::DefenderStrategyRight || mindSet == MindSet::DefenderStrategyLeft || mindSet == MindSet::DefenderStrategy){
		step = 0.6;
	}

	double d = 0.1; // Coeficiente de ponto a frente do robô para ambiente SIMULADO
	if(Config::realEnvironment){
		// Coeficiente para ambiente REAL
		d = 0.3;

		if(mindSet == MindSet::DefenderStrategy) d = 0.5;
	}

	double r = 0.016; // Raio da roda
	double l = 0.075;// Distancia entre as rodas
	double robotAngle = Math::toDomain(Math::toRadian(robot.angle));

	double xdDot = vMax * cos(fi);
	double ydDot = vMax * sin(fi);

	double v = cos(robotAngle) * xdDot + sin(robotAngle) * ydDot;
	double w = -(sin(robotAngle)/d) * xdDot + (cos(robotAngle)/d) * ydDot;

    if ( cos(fi - Math::toRadian(robot.angle)) > 0.3){
        lastSide = -1;
    } else if(cos(fi - Math::toRadian(robot.angle)) < -0.3){
        lastSide = 1;
    }

    double wr = v/r + w*(l/r) * lastSide;
    double wl = v/r - w*(l/r) * lastSide;

	// conversão rad/s para cm/s
	wr =  wr * r * 100;
	wl =  wl * r * 100;

    double linearSpeed = std::abs((wr + wl) / 2);
	double k = 1 - (step * std::abs(linearSpeed - robot.linearSpeed) / 100);

	wr *= k;
	wl *= k;

    //std::cout <<"WR: "<< wr << " WL:" << wl << " Vel Control: " << linearSpeed << " Vel med: "<< robot.linearSpeed << std::endl;

    //	std::cout<<"----"<<std::endl;
    //	std::cout<<"Fi: "<<fi<<std::endl;
    //	std::cout<<"Theta: "<<robotAngle<<std::endl;
    //	std::cout<<"X: "<<robot.position.x<<" Y: "<<robot.position.y<<std::endl;
    //
    //	std::cout<<"v: "<<v<<std::endl;
    //	std::cout<<"w: "<<w<<std::endl;
    //	std::cout<<"wr: "<<wr<<std::endl;
    //	std::cout<<"wl: "<<wl<<std::endl;

	command = checkMaximumSpeedWheel( vss::WheelsCommand(wl, wr));

	return command;
}

vss::WheelsCommand Movimentation::checkMaximumSpeedWheel(const vss::WheelsCommand& speed){
	vss::WheelsCommand command(speed);

	int maximumSpeed = 100;

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
