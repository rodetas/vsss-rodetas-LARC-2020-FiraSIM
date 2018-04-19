//
// Created by manoel on 17/04/18.
//

#include <strategies/RobotStrategyBase.h>

RobotStrategyBase::RobotStrategyBase() = default;

//@TODO: implementar as funcoes daqui

bool RobotStrategyBase::isBlocked(btVector3 target) {
    return false;

}

bool RobotStrategyBase::isParallelToGoal() {
    return false;

}

bool RobotStrategyBase::isStopped() {
    return false;

}

bool RobotStrategyBase::isStoppedFor(int time) {
    return false;

}

bool RobotStrategyBase::isBoard() {
    return false;
}