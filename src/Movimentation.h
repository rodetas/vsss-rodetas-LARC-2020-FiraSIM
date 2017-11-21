#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include "common.h"

using namespace common;

class Movimentation {

private:

    Command movements;

	float maxPwm;

public:

	/**
	 *
	 */
	Movimentation();

	/**
	 *
	 */
	Command movePlayers(Robot*);


	Command turn(Robot*, btVector3, char);

	/**
	 *
	 */
	Command definePwm(Robot*, char);

	Command progressiveAcell(Robot*, Command);

	Command stop();
	Command turnLeft(int, int);
	Command turnRight(int, int);

	void setPotencyFactor(float);
	void setCurveFactor(float);
	Command checkPwm(const Command&);

	Command getMovement();

};
#endif