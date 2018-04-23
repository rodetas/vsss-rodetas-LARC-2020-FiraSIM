#include "movimentation.h"


/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::move_players(RobotState robot, btVector3 target){

	Command command;

	// movement along the field
	if (robot.cosFrom(target) < -0.4) {
		command = define_pwm(robot, target, 'F');

	} else if (robot.cosFrom(target) > 0.4){
		command = define_pwm(robot, target, 'B');

	} else {
		if (robot.sinFrom(target) > 0) {
			command = turn_right(20, 20);
		} else {
			command = turn_left(20, 20);
		}
	}

    return command;
}

/*
 * Correct robot pwm to follow the destination
 */
Command Movimentation::define_pwm(RobotState robot, btVector3 target, char direction){

	int standardPower = 50;
	int basePower = standardPower * 1;//robot.get_potency_factor();
	int correctionPower = standardPower * robot.sinFrom(target) * 0.7;//robot.get_curve_factor();
	int pwmMotor1 = (basePower - correctionPower);
	int pwmMotor2 = (basePower + correctionPower);

	if(direction == 'B'){
		pwmMotor1 = pwmMotor1 * (-1);
		pwmMotor2 = pwmMotor2 * (-1);
	}

	Command verifiedPwm = check_pwm(Command(pwmMotor1, pwmMotor2));

	return verifiedPwm;
}

Command Movimentation::check_pwm(const Command& pwm){
    Command command(pwm);

    if(pwm.left  > 255) command.left  = 255;
    if(pwm.right > 255) command.right = 255;

    if(pwm.left  < -255) command.left  = -255;
    if(pwm.right < -255) command.right = -255;

    return command;
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