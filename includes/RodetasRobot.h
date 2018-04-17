//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_RODETASROBOT_H
#define SDK_RODETAS_RODETASROBOT_H

#include <Mindset.h>
#include <RodetasState.h>
#include <common.h>
#include <RobotState.h>

using namespace common;

class RodetasRobot {

public:

    RodetasRobot();

    void updateSelfState(RodetasRobot);
    void updateState(RodetasState);

    void setMindSet(MindSet);
    void setDebug(Debug&);

private:

    MindSet mindSet;
    Command command;
    Debug debug;
    RodetasState state;
    RobotState robotState;
//    GameStrategy strategy;



};


#endif //SDK_RODETAS_RODETASROBOT_H
