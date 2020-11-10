//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_STRATEGYBASE_H
#define SDK_RODETAS_STRATEGYBASE_H

#include <Config.h>
#include <Domain/Constants.h>
#include <Domain/RobotState.h>
#include <Helpers/TimeHelper.h>
#include <Helpers/Math.h>

class RobotStrategyBase {

public:

    RobotStrategyBase();

    bool isStopped();
    bool isBlocked();
    bool isStoppedFor(double);
    bool isParallelToGoal();
    bool isBoard();

    void update(RobotState, vss::Point);

private:

    RobotState robot;
    vss::Point target;

    TimeHelper timeHelper;
    double stoppedTime;
};

#endif //SDK_RODETAS_STRATEGYBASE_H
