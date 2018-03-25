#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include <common.h>
#include <robot.h>
#include <ball.h>

#include <functional>

using namespace common;

class Movimentation {

public:

	Movimentation() = default;

	virtual Command move_players(Robot, btVector3);

    virtual Command stop();
    virtual Command turn_left(int, int);
    virtual Command turn_right(int, int);

    virtual Command check_pwm(const Command&);
	virtual Command define_pwm(Robot, btVector3, char);

};
#endif