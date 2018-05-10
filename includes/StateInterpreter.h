//
// Created by manoel on 06/05/18.
//

#ifndef SDK_RODETAS_STATEINTERPRETER_H
#define SDK_RODETAS_STATEINTERPRETER_H

#include "common.h"
#include "RodetasRobot.h"

class StateInterpreter {

public:

    StateInterpreter();

    vector<MindSet> defineStrategy(vector<RodetasRobot>&, RodetasState&);

private:

    RodetasRobot getRobotByStrategy(MindSet, vector<RodetasRobot>&);

    int timeLastChange;
    vector<MindSet> strategiesById;

};

#endif //SDK_RODETAS_STATEINTERPRETER_H
