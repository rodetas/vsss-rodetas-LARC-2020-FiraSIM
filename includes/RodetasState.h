//
// Created by manoel on 15/04/18.
//

#ifndef SDK_RODETAS_STATE_H
#define SDK_RODETAS_STATE_H

#include <ball.h>
#include <vector>
#include "RobotState.h"

class RodetasState {

public:

    RodetasState() = default;

    Ball ball;
    std::vector<RobotState> robots;

};

#endif //SDK_RODETAS_STATE_H
