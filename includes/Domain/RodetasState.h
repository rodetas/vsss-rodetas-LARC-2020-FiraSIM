//
// Created by manoel on 15/04/18.
//

#ifndef SDK_RODETAS_STATE_H
#define SDK_RODETAS_STATE_H

#include <vector>
#include <sstream>
#include "Domain/RobotState.h"
#include "Domain/BallState.h"

class RodetasState {

public:

    RodetasState() = default;

    BallState ball;
    std::vector<RobotState> robots;

    std::string toString(){
        std::stringstream ss;
        ss << std::endl << std::endl << "Robots Team 1:" << std::endl;
        for(int i = 0 ; i < 3 ; i++){
            ss << "Robot: (X: " << robots[i].position.x;
            ss << " \tY: " << robots[i].position.y;
            ss << " \tANGLE: " << robots[i].angle;
        }
        ss << std::endl << std::endl << "Robots Team 2:" << std::endl;
        for(int i = 3 ; i < 6 ; i++){
            ss << "Robot: (X: " << robots[i].position.x;
            ss << " \tY: " << robots[i].position.y;
            ss << " \tANGLE: " << robots[i].angle;
        }

        ss << std::endl << std::endl << "Ball:" << std::endl;
        ss << ball.position.x << " " << ball.position.y << std::endl;

        return ss.str();
    }

};

#endif //SDK_RODETAS_STATE_H
