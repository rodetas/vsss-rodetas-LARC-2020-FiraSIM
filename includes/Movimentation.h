#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include <Common.h>
#include <Domain/RobotState.h>
#include <Domain/BallState.h>
#include <Domain/Pose.h>

#include <functional>

using namespace common;

class Movimentation {

public:

	Movimentation() = default;

	virtual Command movePlayers(RobotState, vss::Pose target, float fi);

    virtual Command stop();
    virtual Command turnLeft(int, int);
    virtual Command turnRight(int, int);

    virtual Command checkPwm(const Command&);
	virtual Command definePwm(RobotState, vss::Pose, char, float);

};
#endif
