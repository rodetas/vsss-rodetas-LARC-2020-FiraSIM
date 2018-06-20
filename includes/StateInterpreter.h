//
// Created by manoel on 06/05/18.
//

#ifndef SDK_RODETAS_STATEINTERPRETER_H
#define SDK_RODETAS_STATEINTERPRETER_H

#include <RodetasRobot.h>

class StateInterpreter {

public:

    StateInterpreter();

    std::vector<MindSet> defineStrategy(std::vector<RodetasRobot>&, RodetasState&);

private:

    RodetasRobot getRobotByStrategy(MindSet, std::vector<RodetasRobot>&);

    int timeLastChange;
    std::vector<MindSet> strategiesById;

};

#endif //SDK_RODETAS_STATEINTERPRETER_H
