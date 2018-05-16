//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>

RodetasRobot::RodetasRobot() = default;

RodetasRobot::RodetasRobot(int id, MindSet mind) {
    this->id = id;
    this->mindSet = mind;
}

void RodetasRobot::calcAction(){

    // applies robot strategy returning a pwm
    this->command = strategy->applyStrategy(this->selfState, this->state, this->strategyBase);

    // receives robot target from strategy
    this->debug.robotFinalPose = strategy->getFinalPose();
}

void RodetasRobot::updateSelfState(RobotState selfState) {
    this->selfState = selfState;

    // updates robot's strategy base data
    this->strategyBase.update(selfState, strategy->getFinalPose());
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

int RodetasRobot::getId(){
    return this->id;
}

RobotDebug RodetasRobot::getRobotDebug() {
    return this->debug;
}

RobotState RodetasRobot::getSelfState() {
    return this->selfState;
}

MindSet RodetasRobot::getMindSet() {
    return this->mindSet;
}

void RodetasRobot::setMindSet(MindSet mind){
    this->mindSet = mind;
}

RobotStrategyBase RodetasRobot::getRobotStrategyBase() {
    return this->strategyBase;
}
