#include "Movimentation.h"


/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::movePlayers(RobotState robot, btVector3 target, float fi){

	Command command;

	// movement along the field
	if (robot.cosFrom(target) < -0.4) {
		command = definePwm(robot, target, 'F', fi);

	} else if (robot.cosFrom(target) > 0.4){
		command = definePwm(robot, target, 'B', fi);

	} else {
		if (robot.sinFrom(target) > 0) {
			command = turnRight(20, 20);
		} else {
			command = turnLeft(20, 20);
		}
	}

    return command;
}

/*
 * Correct robot pwm to follow the destination
 */
Command Movimentation::definePwm(RobotState robot, btVector3 target, char direction, float fi){
	int standardPower = 30;
	int basePower = standardPower * 1;//robot.get_potency_factor();
	int correctionPower =20*sin(fi - Math::toRadian(robot.angle));//robot.get_curve_factor();
	int pwmMotor1 = (basePower - correctionPower);
	int pwmMotor2 = (basePower + correctionPower);

	if(direction == 'B'){
		pwmMotor1 = pwmMotor1 * (-1);
		pwmMotor2 = pwmMotor2 * (-1);
	}

	Command verifiedPwm = checkPwm(Command(pwmMotor1, pwmMotor2));

	return verifiedPwm;
}

Command Movimentation::checkPwm(const Command& pwm){
    Command command(pwm);

    if(pwm.left  > 255) command.left  = 255;
    if(pwm.right > 255) command.right = 255;

    if(pwm.left  < -255) command.left  = -255;
    if(pwm.right < -255) command.right = -255;

    return command;
}

Command Movimentation::turnLeft(int pwm1, int pwm2){
	Command command(-pwm1, pwm2);
	return command;
}

Command Movimentation::turnRight(int pwm1, int pwm2){
	Command command(pwm1, -pwm2);
	return command;
}

Command Movimentation::stop(){
	Command command(0, 0);
	return command;
}
