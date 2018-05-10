//
// Created by manoel on 17/04/18.
//

#include <strategies/RobotStrategyBase.h>

RobotStrategyBase::RobotStrategyBase() {
    image = {150,130};
}

void RobotStrategyBase::update(RobotState robot, btVector3 target) {
    this->robot = robot;
    this->target = target;

    if (robot.linearSpeed < 6) stoppedFrames++;
    else stoppedFrames = 0;
}

bool RobotStrategyBase::isBlocked() {
    return (robot.distanceFrom(target) > (24) && isStoppedFor(90));
}

bool RobotStrategyBase::isParallelToGoal() {
    return (robot.cosFrom(btVector3(image.x, robot.position.y)) > -0.3 &&
            robot.cosFrom(btVector3(image.x, robot.position.y)) < 0.3);
}

bool RobotStrategyBase::isStopped() {
    return stoppedFrames > 0;
}

bool RobotStrategyBase::isStoppedFor(int time){
    return stoppedFrames >= time;
}

bool RobotStrategyBase::isBoard() {
    return (robot.position.y > image.y * (0.90) || robot.position.y < image.y * (0.10) ||
            robot.position.x > image.x * (0.85) || robot.position.x < image.x * (0.15) );
}