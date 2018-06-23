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

    std::vector<MindSet> defineStrategy(std::vector<RodetasRobot>&, RodetasState&, bool);

private:

    RodetasRobot getRobotByStrategy(MindSet, std::vector<RodetasRobot>&);

    std::vector<MindSet> strategiesById;

    TimeHelper timeHelper;

};

#endif //SDK_RODETAS_STATEINTERPRETER_H
