//
// Created by manoel on 24/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
#define SDK_RODETAS_ROBOTSTRATEGYFACTORY_H

#include "strategies/RobotStrategy.h"
#include "MathHelper.h"
#include "RodetasState.h"

class RobotStrategyFactory {

public:

    RobotStrategyFactory();
    void manage(RodetasState);

    RobotStrategy* getStrategyForRobot(int);

private:
    //@TODO tirar imageSize
    btVector3 imageSize;

    int timeLastChange;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
