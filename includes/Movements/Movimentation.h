#ifndef MOVIMENTATION_H_
#define MOVIMENTATION_H_

#include <Domain/RobotState.h>
#include <Domain/BallState.h>
#include <Domain/WheelsCommand.h>
#include <Domain/Pose.h>
#include <Domain/RobotSpeed.h>
#include <Domain/Mindset.h>
#include <Config.h>
#include <functional>

class Movimentation {

public:

	Movimentation();

	vss::WheelsCommand movePlayers(RobotState, float, float, vss::Point, vss::Point, RobotSpeed = RobotSpeed::NORMAL, MindSet = MindSet::None);


    vss::WheelsCommand stop();
    vss::WheelsCommand turnLeft(int, int);
    vss::WheelsCommand turnRight(int, int);

    vss::WheelsCommand checkMaximumSpeedWheel(const vss::WheelsCommand& , int);

	int lastSide = 1;
};
#endif
