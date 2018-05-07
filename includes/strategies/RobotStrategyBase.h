//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_STRATEGYBASE_H
#define SDK_RODETAS_STRATEGYBASE_H

#include <common.h>
#include <RobotState.h>

using namespace common;

class RobotStrategyBase {

public:

    RobotStrategyBase();

    bool isStopped();
    bool isBlocked();
    bool isStoppedFor(int);
    bool isParallelToGoal();
    bool isBoard();

    void update(RobotState, btVector3);

private:
    int stoppedFrames;

    RobotState robot;
    btVector3 target;

    //@TODO: tirar image daqui
    btVector3 image;

};

#endif //SDK_RODETAS_STRATEGYBASE_H
