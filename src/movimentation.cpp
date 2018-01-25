#include "movimentation.h"

Movimentation::Movimentation(){
}

/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::move_players(Robot robot, btVector3 target){

	// Vl = v - (w*L)/2
	// Vr = v + (w*L)/2

	Command command;
	btVector3 r(0,0,0); // final orientation
	btVector3 g(0,0,0); // target

	const float n = 1;
	const float D_g = 1;
	const float K_theta = 1;
	const float vmc = 80;

	float d_fi_xc = (((n+1)*(g.y-robot.y())) / (pow(g.y,2) - 2*g.y*robot.y() + pow(g.x,2) - 2*g.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2) )) + n*(robot.y() - r.y)/(pow(r.y,2)-2*r.y*robot.y()+pow(r.x,2)-2*r.x*robot.x()+pow(robot.x(),2)+pow(robot.y(),2));
	float d_fi_yc = ((-(n+1)*(g.x-robot.x())) / (pow(g.y,2) - 2*g.y*robot.y() + pow(g.x,2) - 2*g.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2) )) + n*(r.x - robot.x())/(pow(r.y,2)-2*r.y*robot.y()+pow(r.x,2)-2*r.x*robot.x()+pow(robot.x(),2)+pow(robot.y(),2));

	float fi; // TODO
	float theta_e = 

	btVector3 pc_pg(robot.x()-g.x, robot.y()-g.y);
	float mod_pc_pg = sqrt(pow(robot.x(),2) + pow(robot.y(),2));

	float v = [&](){
		if(mod_pc_pg > D_g){
			v = vmc;
		} else {
			v = (mod_pc_pg/D_g)*vmc;
		}
	}

	float w = [&](){
		float cos_c = cos(robot.angle());
		float sen_c = sin(robot.angle());

		float aux = (d_fi_xc*cos_c + d_fi_yc*sen_c)*v - K_theta*()
	}

	return command;
}

Command Movimentation::check_pwm(const Command& pwm){
 	Command command(pwm);

	if(pwm.left  > 255) command.left  = 255;
	if(pwm.right > 255) command.right = 255;
	
	if(pwm.left  < -255) command.left  = -255;
	if(pwm.right < -255) command.right = -255;

	return command;
}

/*
 * Correct robot pwm to follow the destination
 */
Command Movimentation::define_pwm(Robot robot, btVector3 target, char direction){

	int standardPower = 50;

	int basePower = standardPower * robot.get_potency_factor();
	int correctionPower = standardPower * robot.sin_from(target) * robot.get_curve_factor();
	int pwmMotor1 = (basePower + correctionPower) ;
	int pwmMotor2 = (basePower - correctionPower) ;

	if(direction == 'B'){
		pwmMotor1 = pwmMotor1 * (-1);
		pwmMotor2 = pwmMotor2 * (-1);
	}

	Command verifiedPwm = check_pwm(Command(pwmMotor1, pwmMotor2));

	return verifiedPwm;
}

Command Movimentation::turn_left(int pwm1, int pwm2){
	Command command(-pwm1, pwm2);
	return command;
}

Command Movimentation::turn_right(int pwm1, int pwm2){
	Command command(pwm1, -pwm2);
	return command;
}

Command Movimentation::stop(){
	Command command(0, 0);
	return command;
}