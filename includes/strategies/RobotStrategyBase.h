//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_STRATEGYBASE_H
#define SDK_RODETAS_STRATEGYBASE_H

#include <common.h>

using namespace common;

class RobotStrategyBase {

public:

    RobotStrategyBase();

    bool isStopped();
    bool isBlocked(btVector3);
    bool isStoppedFor(int);
    bool isParallelToGoal();
    bool isBoard();

};

#endif //SDK_RODETAS_STRATEGYBASE_H
