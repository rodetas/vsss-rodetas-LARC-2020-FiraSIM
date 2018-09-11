//
// Created by manoel on 23/06/18.
//

#include <Domain/Mindset.h>

std::string toString(MindSet m){
    switch(m){
        case MindSet::GoalKeeper:
            return "GoalKeeper";
        case MindSet::Defender:
            return "Defender";
        case MindSet::Attacker:
            return "Attacker";
        default:
            return "";
    }
}
