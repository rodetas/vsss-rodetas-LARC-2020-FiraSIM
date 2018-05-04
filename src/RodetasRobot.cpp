//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>

RodetasRobot::RodetasRobot() = default;

void RodetasRobot::calcAction(){
    // updates robot's strategy base data
    this->strategyBase.updateStopped(selfState);

    // applies robot strategy returning a pwm
    this->command = strategy->applyStrategy(this->selfState, this->state, this->strategyBase);

    // receives robot target from strategy
    this->debug.robotFinalPose = strategy->getFinalPose();
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

void RodetasRobot::setStrategy(RobotStrategy* s) {
    this->strategy = s;
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

RobotStrategyBase RodetasRobot::getRobotStrategyBase() {
    return this->strategyBase;
}
