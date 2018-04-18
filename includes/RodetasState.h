//
// Created by manoel on 15/04/18.
//

#ifndef SDK_RODETAS_STATE_H
#define SDK_RODETAS_STATE_H

#include <vector>
#include "RobotState.h"
#include "BallState.h"

class RodetasState {

public:

    RodetasState() = default;

    BallState ball;
    std::vector<RobotState> robots;

};

#endif //SDK_RODETAS_STATE_H
