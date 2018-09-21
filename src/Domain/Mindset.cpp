//
// Created by manoel on 23/06/18.
//

#include <Domain/Mindset.h>

// retorna um vector com os MindSet que representam uma estrategia
std::vector<MindSet> getStrategiesMindSet(){
    return {MindSet::GoalKeeperStrategy, MindSet::DefenderStrategy, MindSet::DefenderBackStrategy, MindSet::AttackerStrategy, MindSet::DefenderStrategyLeft, MindSet::DefenderStrategyRight};
}

std::string toString(MindSet m){
    switch(m){
        case MindSet::None:
            return "None";
        case MindSet::GoalKeeperStrategy:
            return "GoalKeeperStrategy";
        case MindSet::DefenderStrategy:
            return "DefenderStrategy";
        case MindSet::DefenderBackStrategy:
            return "DefenderBackStrategy";
        case MindSet::AttackerStrategy:
            return "AttackerStrategy";
        case MindSet::PenaltyHitAttackPositioning:
            return "PenaltyHitAttackPositioning";
        case MindSet::PenaltyHitDefenderPositioning:
            return "PenaltyHitDefenderPositioning";
        case MindSet::PenaltyAgainstAttackPositioning:
            return "PenaltyAgainstAttackPositioning";
        case MindSet::PenaltyAgainstDefenderPositioning:
            return "PenaltyAgainstDefenderPositioning";
        case MindSet::GoalKeeperCenterPositioning:
            return "GoalKeeperCenterPositioning";
        case MindSet ::DefenderStrategyLeft:
            return "DefenderStrategyLeft";
        case MindSet ::DefenderStrategyRight:
            return "DefenderStrategyRight";
        default:
            return "NotDefined";
    }
}
