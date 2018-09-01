//
// Created by manoel on 24/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
#define SDK_RODETAS_ROBOTSTRATEGYFACTORY_H

//#include "Strategies/RobotStrategy.h"
//#include "Helpers/MathHelper.h"
#include <Domain/RodetasState.h>
#include <Domain/PositionStatus.h>
#include <RodetasRobot.h>
#include <StateInterpreter.h>
#include <Strategies/RobotStrategyBase.h>
#include <Strategies/RobotStrategyAttack.h>
#include <Strategies/RobotStrategyDefender.h>
#include <Strategies/RobotStrategyGoal.h>

class RobotStrategyFactory {

public:

    RobotStrategyFactory();
    void manage(std::vector<RodetasRobot>&, RodetasState&, bool, bool, PositionStatus);

private:

    StateInterpreter interpreter;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
