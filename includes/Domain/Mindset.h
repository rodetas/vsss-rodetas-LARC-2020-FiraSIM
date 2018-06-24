//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MINDSET_H
#define SDK_RODETAS_MINDSET_H

#include <string>

enum MindSet {
    GoalKeeper  = 0,
    Defender    = 1,
    Attacker    = 2
};

std::string toString(MindSet);

#endif //SDK_RODETAS_MINDSET_H
