//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_STRATEGYBASE_H
#define SDK_RODETAS_STRATEGYBASE_H

#include <Config.h>
#include <Domain/Constants.h>
#include <Domain/RobotState.h>

class RobotStrategyBase {

public:

    RobotStrategyBase();

    bool isStopped();
    bool isBlocked();
    bool isStoppedFor(int);
    bool isParallelToGoal();
    bool isBoard();

    void update(RobotState, vss::Point);

private:
    int stoppedFrames;

    RobotState robot;
    vss::Point target;

};

#endif //SDK_RODETAS_STRATEGYBASE_H
