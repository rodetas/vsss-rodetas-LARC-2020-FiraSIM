//
// Created by manoel on 17/04/18.
//

#include <Strategies/RobotStrategyBase.h>

RobotStrategyBase::RobotStrategyBase() = default;

void RobotStrategyBase::update(RobotState robot, vss::Point target) {
    this->robot = robot;
    this->target = target;

    if (robot.linearSpeed < 10){
        stoppedTime = timeHelper.getElapsedTime();
        if(stoppedTime > 20000) stoppedTime = 20000;
    } else {
        timeHelper.restartCounting();
        stoppedTime = 0;
    }
}

bool RobotStrategyBase::isBlocked() {
    return (robot.distanceFrom(target) > 25 && isStoppedFor(3000));
}

bool RobotStrategyBase::isParallelToGoal() {
    return (robot.cosFrom(vss::Point(vss::MAX_COORDINATE_X, robot.position.y)) > -0.3 &&
            robot.cosFrom(vss::Point(vss::MAX_COORDINATE_X, robot.position.y)) < 0.3);
}

bool RobotStrategyBase::isStopped() {
    return stoppedTime > 300;
}

bool RobotStrategyBase::isStoppedFor(double time){
    return stoppedTime >= time;
}

bool RobotStrategyBase::isBoard() {
    return (robot.position.y > vss::MAX_COORDINATE_Y * (0.93) || robot.position.y < vss::MAX_COORDINATE_Y * (0.06) ||
            robot.position.x > vss::MAX_COORDINATE_X * (0.88) || robot.position.x < vss::MAX_COORDINATE_X * (0.12) );
}