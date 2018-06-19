//
// Created by manoel on 17/04/18.
//

#include <strategies/RobotStrategyBase.h>
#include <Config.h>

RobotStrategyBase::RobotStrategyBase() = default;

void RobotStrategyBase::update(RobotState robot, vss::Point target) {
    this->robot = robot;
    this->target = target;

    if (robot.linearSpeed < 6) stoppedFrames++;
    else stoppedFrames = 0;
}

bool RobotStrategyBase::isBlocked() {
    return (robot.distanceFrom(target) > (24) && isStoppedFor(90));
}

bool RobotStrategyBase::isParallelToGoal() {
    return (robot.cosFrom(vss::Point(Config::fieldSize.x, robot.position.y)) > -0.3 &&
            robot.cosFrom(vss::Point(Config::fieldSize.x, robot.position.y)) < 0.3);
}

bool RobotStrategyBase::isStopped() {
    return stoppedFrames > 0;
}

bool RobotStrategyBase::isStoppedFor(int time){
    return stoppedFrames >= time;
}

bool RobotStrategyBase::isBoard() {
    return (robot.position.y > Config::fieldSize.y * (0.90) || robot.position.y < Config::fieldSize.y * (0.10) ||
            robot.position.x > Config::fieldSize.x * (0.85) || robot.position.x < Config::fieldSize.x * (0.15) );
}