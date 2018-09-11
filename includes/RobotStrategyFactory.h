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
#include <Strategies/RobotStrategyAttack.h>
#include <Strategies/RobotStrategyDefender.h>
#include <Strategies/RobotStrategyDefenderBack.h>
#include <Strategies/RobotStrategyGoal.h>
#include <Positioning/Penalty/AttackPenaltyPositioning.h>

class RobotStrategyFactory {

public:

    RobotStrategyFactory();
    void manage(std::vector<RodetasRobot>&, RodetasState&, bool, bool, PositionStatus);
    void manageStrategies(std::vector<RodetasRobot>&, RodetasState&, bool);
    void managePositioning(std::vector<RodetasRobot>&, RodetasState&, PositionStatus);

private:

    StateInterpreter interpreter;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
