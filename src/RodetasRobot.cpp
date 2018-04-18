//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>

RodetasRobot::RodetasRobot() {

}

void RodetasRobot::calcAction(){
    //strategy->apply((RodetasRobot&)this);
}

void RodetasRobot::updateSelfState(RobotState selfState) {
    this->selfState = selfState;
}

void RodetasRobot::updateState(RodetasState state){
    this->state = state;
}

void RodetasRobot::setDebug(RobotDebug debug) {
    this->debug = debug;
}

Command RodetasRobot::getCommand(){
    return this->command;
}

RobotDebug RodetasRobot::getRobotDebug() {
    return this->debug;
}

RobotState RodetasRobot::getSelfState() {
    return this->selfState;
}
