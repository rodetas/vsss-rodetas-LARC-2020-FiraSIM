//
// Created by manoel on 24/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
#define SDK_RODETAS_ROBOTSTRATEGYFACTORY_H

#include "strategies/RobotStrategy.h"
#include "RodetasState.h"

class RobotStrategyFactory {

public:

    void manage(RodetasState);

    RobotStrategy* getStrategyForRobot(int);

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
