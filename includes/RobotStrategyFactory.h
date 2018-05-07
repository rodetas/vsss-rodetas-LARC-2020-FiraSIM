//
// Created by manoel on 24/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
#define SDK_RODETAS_ROBOTSTRATEGYFACTORY_H

#include "strategies/RobotStrategy.h"
#include "MathHelper.h"
#include "RodetasState.h"
#include "RodetasRobot.h"
#include "StateInterpreter.h"
#include <strategies/RobotStrategyBase.h>
#include <strategies/RobotStrategyAttack.h>
#include <strategies/RobotStrategyDefender.h>
#include <strategies/RobotStrategyGoal.h>

class RobotStrategyFactory {

public:

    RobotStrategyFactory();
    void manage(vector<RodetasRobot>&, RodetasState&);

private:

    StateInterpreter interpreter;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
