//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MINDSET_H
#define SDK_RODETAS_MINDSET_H

#include <string>
#include <vector>

enum class MindSet {
    None,
    GoalKeeperStrategy,
    DefenderStrategy,
    DefenderBackStrategy,
    AttackerStrategy,

    PenaltyAttackPositioning,
    PenaltyDefenderPositioning
    // ...
};


std::vector<MindSet> getStrategiesMindSet();

std::string toString(MindSet);

#endif //SDK_RODETAS_MINDSET_H
