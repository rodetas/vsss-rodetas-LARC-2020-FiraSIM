#include "Movements/Movimentation.h"


/*
 * calculates the basic movimentation to goal to target
 */
vss::WheelsCommand Movimentation::movePlayers(RobotState robot, vss::Pose target, float fi){

    vss::WheelsCommand command;

	if ( cos(fi - Math::toRadian(robot.angle)) < -0.4) {
		command = definePwm(robot, target, 'B', fi);
	} else if ( cos(fi - Math::toRadian(robot.angle)) > 0.4){
		command = definePwm(robot, target, 'F', fi);
	}else{
		if (sin(fi - Math::toRadian(robot.angle)) > 0) {
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
vss::WheelsCommand Movimentation::definePwm(RobotState robot, vss::Pose target, char direction, float fi){
	int standardPower = 50;
	int basePower = standardPower * 1;
	int correctionPower = standardPower * sin(fi - Math::toRadian(robot.angle)) * 0.8;
	int pwmMotor1 = (basePower + correctionPower);
	int pwmMotor2 = (basePower - correctionPower);

	if(direction == 'B'){
		pwmMotor1 = pwmMotor1 * (-1);
		pwmMotor2 = pwmMotor2 * (-1);
	}

    vss::WheelsCommand verifiedPwm = checkPwm(vss::WheelsCommand(pwmMotor1, pwmMotor2));

	return verifiedPwm;
}

vss::WheelsCommand Movimentation::checkPwm(const vss::WheelsCommand& pwm){
    vss::WheelsCommand command(pwm);

    if(pwm.leftVel  > 255) command.leftVel  = 255;
    if(pwm.rightVel > 255) command.rightVel = 255;

    if(pwm.leftVel  < -255) command.leftVel  = -255;
    if(pwm.rightVel < -255) command.rightVel = -255;

    return command;
}

vss::WheelsCommand Movimentation::turnLeft(int pwm1, int pwm2){
    vss::WheelsCommand command(-pwm1, pwm2);
	return command;
}

vss::WheelsCommand Movimentation::turnRight(int pwm1, int pwm2){
    vss::WheelsCommand command(pwm1, -pwm2);
	return command;
}

vss::WheelsCommand Movimentation::stop(){
    vss::WheelsCommand command(0, 0);
	return command;
}
