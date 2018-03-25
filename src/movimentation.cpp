#include <movimentation.h>

/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::move_players(Robot robot, btVector3 target){

	Command command;
    btVector3 r = btVector3(target.x+10, target.y); // final orientation
    btVector3 g = target; // target

/*	const float n = 3.f;
	const float D_g = 100.f;
	const float K_omega = 3.f;
	const float vmc = 20.f;
*/

    float fi = define_fi(robot, r, g);

    command.left = 80 - 50*sin(fi - robot.rad_angle());
    command.right = 80 + 50*sin(fi - robot.rad_angle());

    /*
    double d_fi_xc = (((n + 1) * (g.y - robot.y())) /
                      (pow(g.y, 2) - 2 * g.y * robot.y() + pow(g.x, 2) - 2 * g.x * robot.x() + pow(robot.x(), 2) +
                       pow(robot.y(), 2))) + n * (robot.y() - r.y) /
                                             (pow(r.y, 2) - 2 * r.y * robot.y() + pow(r.x, 2) -
                                              2 * r.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2));
    double d_fi_yc = ((-(n + 1) * (g.x - robot.x())) /
                      (pow(g.y, 2) - 2 * g.y * robot.y() + pow(g.x, 2) - 2 * g.x * robot.x() + pow(robot.x(), 2) +
                       pow(robot.y(), 2))) + n * (r.x - robot.x()) /
                                             (pow(r.y, 2) - 2 * r.y * robot.y() + pow(r.x, 2) -
                                              2 * r.x * robot.x() + pow(robot.x(), 2) + pow(robot.y(), 2));

    float fi = define_fi(robot, r, g);
    float theta_e = robot.rad_angle() - fi;
    //cout << "THETA: " << robot.rad_angle() << " FI: " << fi << " ERRO: " << theta_e << endl;

    btVector3 pc_pg(robot.x() - g.x, robot.y() - g.y);
    double mod_pc_pg = sqrt(pow(pc_pg.x, 2) + pow(pc_pg.y, 2));

    double v = [&]() {
        if (mod_pc_pg > D_g) {
            v = vmc;
        } else {
            v = (mod_pc_pg / D_g) * vmc;
        }

        return v;
    }();

    double w = [&]() {

        float cos_c = cos(robot.rad_angle());
        float sen_c = sin(robot.rad_angle());
        float sgn_func = [&]() {
            if (theta_e < 0) return -1;
            return 1;
        }();

        w = (d_fi_xc * cos_c + d_fi_yc * sen_c) * v - K_omega * sgn_func * sqrt(fabs(theta_e));
        return w;
    }();
*/

    cout << "FI: " << sin(fi) << endl;
	//cout << "V: " << v << "\t\t W: " << w << endl;
	cout << "1: " << command.left << "\t 2: " << command.right << endl;
	return command;
}

float Movimentation::define_fi(Robot& p, btVector3 r, btVector3 g){

	float theta_pr = atan2((r.y - p.y()),(r.x-p.x()));
	float theta_pg = atan2((g.y - p.y()),(g.x-p.x()));

	float alpha = theta_pr - theta_pg;
    float fi = theta_pg - 1.7*alpha;

	// just for draw purposes
	float coss = cos(fi);
    float sen = sin(fi);
	p.set_potencial_direction(btVector3((p.x() + coss)*1.2f, (p.y() + sen)*1.2f));

	return fi;

}

Command Movimentation::check_pwm(const Command& pwm){
 	Command command(pwm);

	if(pwm.left  > 80) command.left  = 80;
	if(pwm.right > 80) command.right = 80;
	
	if(pwm.left  < 0) command.left  = 0;
	if(pwm.right < 0) command.right = 0;

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