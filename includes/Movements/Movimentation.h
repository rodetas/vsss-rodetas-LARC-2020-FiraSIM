#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include <Domain/RobotState.h>
#include <Domain/BallState.h>
#include <Domain/WheelsCommand.h>
#include <Domain/Pose.h>
#include <functional>

class Movimentation {

public:

	Movimentation() = default;

	vss::WheelsCommand movePlayers(RobotState, vss::Pose target, float fi);

    vss::WheelsCommand stop();
    vss::WheelsCommand turnLeft(int, int);
    vss::WheelsCommand turnRight(int, int);

    vss::WheelsCommand checkMaximumSpeedWheel(const vss::WheelsCommand&);
};
#endif
