#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include "common.h"
#include "Robot.h"
#include "Ball.h"

using namespace common;

class Movimentation {

public:

	Movimentation();

	Command movePlayers(Robot, btVector3);
	
	Command stop();
	Command turnLeft(int, int);
	Command turnRight(int, int);

	Command checkPwm(const Command&);
	Command definePwm(Robot, btVector3, char);
	
	void setPotencyFactor(float);
	void setCurveFactor(float);
};
#endif