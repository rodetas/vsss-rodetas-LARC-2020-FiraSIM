//
// Created by manoel on 23/06/18.
//

#include <Domain/Mindset.h>

// retorna um vector com os MindSet que representam uma estrategia
std::vector<MindSet> getStrategiesMindSet(){
    return {MindSet::GoalKeeperStrategy, MindSet::DefenderStrategy, MindSet::DefenderBackStrategy, MindSet::AttackerStrategy, MindSet::DefenderStrategyLeft, MindSet::DefenderStrategyRight, MindSet::CenterAttackerStrategy, MindSet::ForwardAttackerStrategy, MindSet::SideAttackerStrategy};
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
        case MindSet::AttackMiddleDefensePositioning:
            return "AttackMiddleDefensePositioning";
        case MindSet::DefenderMiddleDefensePositioning:
            return "DefenderMiddleDefensePositioning";
        case MindSet::AttackMiddleAttackPositioning:
            return "AttackMiddleAttackPositioning";
        case MindSet::DefenderMiddleAttackPositioning:
            return "DefenderMiddleAttackPositioning";
        case MindSet::AttackFreeballLeftAttackPositioning:
            return "AttackFreeballLeftAttackPositioning";
        case MindSet::AttackFreeballLeftDefensePositioning:
            return "AttackFreeballLeftDefensePositioning";
        case MindSet::AttackFreeballRightAttackPositioning:
            return "AttackFreeballRightAttackPositioning";
        case MindSet::DefenseFreeballPositioning:
            return "AttackFreeballLeftDefensePositioning";
        case MindSet::AttackFreeballRightDefensePositioning:
            return "AttackFreeballRightDefensePositioning";
        case MindSet::GoalKeeperCenterPositioning:
            return "GoalKeeperCenterPositioning";
        case MindSet ::DefenderStrategyLeft:
            return "DefenderStrategyLeft";
        case MindSet ::DefenderStrategyRight:
            return "DefenderStrategyRight";
        case MindSet::SideAttackerStrategy:
            return "SideAttackerStrategy";
        case MindSet::CenterAttackerStrategy:
            return "CenterAttackerStrategy";
        case MindSet::ForwardAttackerStrategy:
            return "ForwardAttackerStrategy";
        case MindSet::AttackDefenseStrategy:
            return "AttackDefenseStrategy";
        default:
            return "NotDefined";
    }
}
