//
// Created by manoel on 06/05/18.
//

#ifndef SDK_RODETAS_STATEINTERPRETER_H
#define SDK_RODETAS_STATEINTERPRETER_H

#include <RodetasRobot.h>
#include <Helpers/TimeHelper.h>

class StateInterpreter {

public:

    StateInterpreter();

    std::vector<MindSet> manageStrategyOrPositioning(std::vector<RodetasRobot> &, RodetasState &, bool, bool, PositionStatus);
    std::vector<MindSet> defineStrategy(std::vector<RodetasRobot>&, RodetasState&, bool);

    std::vector<MindSet> definePositioning(std::vector<RodetasRobot>&, RodetasState&, PositionStatus);

    void defineStandartStrategies(std::vector<RodetasRobot>&, RodetasState&, bool fixed=false);
    void definePenaltyHit(std::vector<RodetasRobot>&, RodetasState&);
    void definePenaltyAgainst(std::vector<RodetasRobot>&, RodetasState&);
    void defineMiddleAttack(std::vector<RodetasRobot>&, RodetasState&);
    void defineMiddleDefense(std::vector<RodetasRobot>&, RodetasState&);
    void chooseStrategies(std::vector<RodetasRobot>&, RodetasState&, bool);
    bool doesAllRobotsHaveStrategy(std::vector<RodetasRobot>&);

    RodetasRobot getClosestRobotTo(std::vector<RodetasRobot>&, vss::Point);
    std::vector<RodetasRobot> getClosestRobots(std::vector<RodetasRobot>&, vss::Point);

private:

    RodetasRobot getRobotByStrategy(MindSet, std::vector<RodetasRobot>&);

    std::vector<MindSet> strategiesById;

    TimeHelper timeHelper;
    TimeHelper timeAfterPositioning;

    PositionStatus lastPosStatus;

};

#endif //SDK_RODETAS_STATEINTERPRETER_H
