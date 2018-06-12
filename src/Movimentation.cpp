#include "Movimentation.h"


/*
 * calculates the basic movimentation to goal to target
 */
Command Movimentation::movePlayers(RobotState robot, btVector3 target, float fi){

	Command command;

	//std::cout << cos(fi - Math::toRadian(robot.angle)) << std::endl;

	if ( cos(fi - Math::toRadian(robot.angle)) < 0) {
		command = definePwm(robot, target, 'B', fi);
	} else if ( cos(fi - Math::toRadian(robot.angle)) > 0){
		command = definePwm(robot, target, 'F', fi);
	}

  return command;
}

/*
 * Correct robot pwm to follow the destination
 */
Command Movimentation::definePwm(RobotState robot, btVector3 target, char direction, float fi){
	int standardPower = 50;
	int basePower = standardPower * 1;
	int correctionPower = standardPower * sin(fi - Math::toRadian(robot.angle)) * 0.8;
	int pwmMotor1 = (basePower + correctionPower);
	int pwmMotor2 = (basePower - correctionPower);

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
