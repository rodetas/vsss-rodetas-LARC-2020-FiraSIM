//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_STRATEGYBASE_H
#define SDK_RODETAS_STRATEGYBASE_H

#include <Common.h>
#include <RobotState.h>

using namespace common;

class RobotStrategyBase {

public:

    RobotStrategyBase();

    bool isStopped();
    bool isBlocked(RobotState, btVector3);
    bool isStoppedFor(int);
    bool isParallelToGoal(RobotState);
    bool isBoard(RobotState);

    void updateStopped(RobotState);

private:
    int stoppedFrames;

    //@TODO: tirar image daqui
    btVector3 image;

};

#endif //SDK_RODETAS_STRATEGYBASE_H
