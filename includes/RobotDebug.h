//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_ROBOTDEBUG_H
#define SDK_RODETAS_ROBOTDEBUG_H

#include <common.h>

class RobotDebug {

public:

    common::btVector3 robotStepPose;
    common::btVector3 robotFinalPose;
    common::Path path;


};

#endif //SDK_RODETAS_ROBOTDEBUG_H
