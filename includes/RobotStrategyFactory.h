//
// Created by manoel on 24/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
#define SDK_RODETAS_ROBOTSTRATEGYFACTORY_H

#include <Domain/RodetasState.h>
#include <Domain/PositionStatus.h>
#include <RodetasRobot.h>
#include <StateInterpreter.h>
#include <Strategies/RobotStrategyAttack.h>
#include <Strategies/RobotStrategyDefender.h>
#include <Strategies/RobotStrategyGoal.h>
#include <Strategies/RobotStrategyDefenderRight.h>
#include <Strategies/RobotStrategyDefenderLeft.h>
#include <Positioning/Penalty/AttackPenaltyHitPositioning.h>
#include <Positioning/Penalty/AttackPenaltyAgainstPositioning.h>
#include <Positioning/Penalty/DefenderPenaltyHitPositioning.h>
#include <Positioning/Penalty/DefenderPenaltyAgainstPositioning.h>
#include <Positioning/GoalKeeperCenterPositioning.h>

class RobotStrategyFactory {

public:

    RobotStrategyFactory();
    void manage(std::vector<RodetasRobot>&, RodetasState&, bool, bool, PositionStatus);
    void constructStrategies(std::vector<RodetasRobot>&, std::vector<MindSet>&);

private:

    StateInterpreter interpreter;
    TimeHelper timeHelper;

};

#endif //SDK_RODETAS_ROBOTSTRATEGYFACTORY_H
