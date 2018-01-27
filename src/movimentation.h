#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include "common.h"
#include "robot.h"
#include "ball.h"

#include <functional>

using namespace common;

class Movimentation {

public:

	Movimentation();

	Command move_players(Robot, btVector3);

	Command stop();
	Command turn_left(int, int);
	Command turn_right(int, int);

	Command check_pwm(const Command&);
	Command define_pwm(Robot, btVector3, char);

};
#endif