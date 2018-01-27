#include "movimentation.h"

Movimentation::Movimentation(){
}

/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::move_players(Robot& robot, btVector3 target){

	Command command;
	btVector3 r = btVector3(target.x+10, target.y); // final orientation
	btVector3 g = target; // target

	const float n = 3;
	const float D_g = 3;
	const float K_omega = 3;
	const float vmc = 20;

	float d_fi_xc = (((n+1)*(g.y-robot.y())) / (pow(g.y,2) - 2*g.y*robot.y() + pow(g.x,2) - 2*g.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2) )) + n*(robot.y() - r.y)/(pow(r.y,2)-2*r.y*robot.y()+pow(r.x,2)-2*r.x*robot.x()+pow(robot.x(),2)+pow(robot.y(),2));
	float d_fi_yc = ((-(n+1)*(g.x-robot.x())) / (pow(g.y,2) - 2*g.y*robot.y() + pow(g.x,2) - 2*g.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2) )) + n*(r.x - robot.x())/(pow(r.y,2)-2*r.y*robot.y()+pow(r.x,2)-2*r.x*robot.x()+pow(robot.x(),2)+pow(robot.y(),2));

	float fi = define_fi(robot, r, g);
	float theta_e = robot.rad_angle() - fi;
	cout << "THETA: " << robot.rad_angle() << " FI: " << fi << " ERRO: " << theta_e << endl;

	btVector3 pc_pg(robot.x()-g.x, robot.y()-g.y);
	float mod_pc_pg = sqrt(pow(pc_pg.x,2) + pow(pc_pg.y,2));

	float v = [&](){
		if(mod_pc_pg > D_g){
			v = vmc;
		} else {
			v = (mod_pc_pg/D_g)*vmc;
		}

		return v;
	}();

	float w = [&](){

		float cos_c = cos(robot.rad_angle());
		float sen_c = sin(robot.rad_angle());
		float sgn_func = [&](){
			if(theta_e < 0) return -1;
			return 1;
		}();

		w = (d_fi_xc*cos_c + d_fi_yc*sen_c)*v - K_omega*sgn_func*sqrt(fabs(theta_e));
		return w;
	}();


	command.left = v - (w*8)/2;
	command.right = v + (w*8)/2;

	cout << "FI: " << fi << endl;
	cout << "V: " << v << "\t\t W: " << w << endl;
	cout << "1: " << command.left << "\t 2: " << command.right << endl;

	return check_pwm(command);
}

float Movimentation::define_fi(Robot& p, btVector3 r, btVector3 g){

	float theta_pr = atan2((r.y - p.y()),(r.x-p.x()));
	float theta_pg = atan2((g.y - p.y()),(g.x-p.x()));

	float alpha = theta_pr - theta_pg;
    float fi = theta_pg - 1*alpha;

	// just for draw purposes
	float coss = cos(fi);
    float sen = sin(fi);
	p.set_potencial_direction(btVector3((p.x() + coss)*1.2, (p.y() + sen)*1.2));

	return fi;
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