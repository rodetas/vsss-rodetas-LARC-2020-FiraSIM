//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>

RodetasRobot::RodetasRobot() = default;

RodetasRobot::RodetasRobot(int id, MindSet mind, Agent* strategy) {
    this->id = id;
    this->mindSet = mind;
    this->agent = strategy;
}

void RodetasRobot::calcAction(){

    // applies robot strategy returning a pwm
    this->command = agent->applyStrategy(this->selfState, this->state, this->strategyBase);

    this->target = agent->getFinalPose();
    this->path = agent->getPath();
}

void RodetasRobot::updateSelfState(RobotState selfState) {
    this->selfState = selfState;

    // updates robot's strategy base data
    this->strategyBase.update(selfState, agent->getFinalPose());
}

void RodetasRobot::updateState(RodetasState state){
    this->state = state;
}

void RodetasRobot::setStrategy(RobotStrategy* s) {
    this->agent = s;
}

vss::WheelsCommand RodetasRobot::getCommand(){
    return this->command;
}

int RodetasRobot::getId(){
    return this->id;
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

vss::Path RodetasRobot::getPath(){
    return path;
}

vss::Pose RodetasRobot::getFinalPose(){
    return target;
}

vss::Point RodetasRobot::getStepPoint(){
    return stepPoint;
}
