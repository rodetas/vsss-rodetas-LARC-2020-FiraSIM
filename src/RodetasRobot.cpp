//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>

RodetasRobot::RodetasRobot() {

}

void RodetasRobot::updateSelfState(Robot selfState) {
    this->selfState.x = selfState.x;
}

void RodetasRobot::updateState(RodetasState state){
    this->state = state;
}

void RodetasRobot::setMindSet(MindSet mind) {
    this->mindSet = mind;

    switch(mindSet){
        case MindSet::GoalKeeper:
            // strategy = goalKeeper()
            break;
        case MindSet::Defender:
            // strategy = defender()
            break;
        case MindSet::Attacker:
            // strategy = attacker()
            break;
    }

}

void RodetasRobot::setDebug(Debug& debug) {
    this->debug = debug;
}
