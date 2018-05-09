#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include <Common.h>
#include <RobotState.h>
#include <BallState.h>

#include <functional>

using namespace common;

class Movimentation {

public:

	Movimentation() = default;

	virtual Command movePlayers(RobotState, btVector3);

    virtual Command stop();
    virtual Command turnLeft(int, int);
    virtual Command turnRight(int, int);

    virtual Command checkPwm(const Command&);
	virtual Command definePwm(RobotState, btVector3, char);

};
#endif
