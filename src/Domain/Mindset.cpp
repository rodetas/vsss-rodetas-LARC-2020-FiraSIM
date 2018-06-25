//
// Created by manoel on 23/06/18.
//

#include <Domain/Mindset.h>

std::string toString(MindSet m){
    switch(m){
        case GoalKeeper:
            return "GoalKeeper";
        case Defender:
            return "Defender";
        case Attacker:
            return "Attacker";
        default:
            return "";
    }
}
