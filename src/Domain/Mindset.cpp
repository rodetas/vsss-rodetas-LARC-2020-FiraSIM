//
// Created by manoel on 23/06/18.
//

#include <Domain/Mindset.h>

// retorna um vector com os MindSet que representam uma estrategia
std::vector<MindSet> getStrategiesMindSet(){
    return {MindSet::GoalKeeperStrategy, MindSet::DefenderStrategy, MindSet::DefenderBackStrategy, MindSet::AttackerStrategy};
}

std::string toString(MindSet m){
    switch(m){
        case MindSet::GoalKeeperStrategy:
            return "GoalKeeper";
        case MindSet::DefenderStrategy:
            return "Defender";
        case MindSet::AttackerStrategy:
            return "Attacker";
        default:
            return "";
    }
}
