#include "Movements/Movimentation.h"


Movimentation::Movimentation() = default;

/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, float fi, int speed){

	vss::WheelsCommand command;
	//std::cout<<"Velocidade que chega: "<<speed<<std::endl;
	double vMax = 0.6;
	double d = 0.081;
	if(speed == 3){ 
	 	vMax = 0.4;
		d = 0.1;
	 }
	/*else if(speed == 2) 
	{
		vMax = 1.2;
		d = 0.54;	
	}
	else if(speed == 3) 
	{	
		vMax = 0.8;
	}*/
	 // Coeficiente de ponto a frente do robô para ambiente SIMULADO
	/*if(Config::realEnvironment){
		// Coeficiente para ambiente REAL
		d = 0.2;
	}*/

	double r = 0.016; // Raio da roda
	double l = 0.075;// Distancia entre as rodas
	double robotAngle = Math::toDomain(Math::toRadian(robot.angle));

	double xdDot = vMax * cos(fi);
	double ydDot = vMax * sin(fi);

	double v = cos(robotAngle) * xdDot + sin(robotAngle) * ydDot;
	double w = -(sin(robotAngle)/d) * xdDot + (cos(robotAngle)/d) * ydDot;

    if ( cos(fi - Math::toRadian(robot.angle)) > 0.4){
        lastSide = -1;
    } else if(cos(fi - Math::toRadian(robot.angle)) < -0.4){
        lastSide = 1;
    }

    double wr = v/r + w*(l/r) * lastSide;
    double wl = v/r - w*(l/r) * lastSide;

	// conversão rad/s para cm/s
	//wr =  wr * r * 100;
	//wl =  wl * r * 100;

    //double linearSpeed = std::abs((wr + wl) / 2);
	//double k = 1 - (0.7 * std::abs(linearSpeed - robot.linearSpeed) / 60);
	//std::cout<<"k:"<<k<<std::endl;

	//wr *= k;
	//wl *= k;
	//std::cout<<"Fi: "<<Math::toDomain(fi)<<" Vcontrol: "<<v<<" Wcontrol: "<<w<<" Wr: "<<wr<< "Wl: "<<wl<<" --- X: "<<robot.position.x<<" Y: "<<robot.position.y<<" Theta: "<<robotAngle<<" Vrobot: "<<robot.linearSpeed<<" Wrobot: "<<Math::toDomain(robot.angularSpeed)<<" Eangle:"<<Math::toDomain(fi - robotAngle)<<std::endl;


	command = checkMaximumSpeedWheel( vss::WheelsCommand(wl, wr));

	return command;
}

vss::WheelsCommand Movimentation::checkMaximumSpeedWheel(const vss::WheelsCommand& speed){
	vss::WheelsCommand command(speed);

	int maximumSpeed = 60;

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
