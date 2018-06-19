//
// Created by manoel on 15/04/18.
//

#ifndef SDK_RODETAS_STATE_H
#define SDK_RODETAS_STATE_H

#include <vector>
#include "Domain/RobotState.h"
#include "Domain/BallState.h"

class RodetasState {

public:

    RodetasState() = default;

    BallState ball;
    std::vector<RobotState> robots;

    string toString(){
        stringstream ss;
        ss << endl << endl << "Robots Team 1:" << endl;
        for(int i = 0 ; i < 3 ; i++){
            ss << "Robot: (X: " << robots[i].position.x;
            ss << " \tY: " << robots[i].position.y;
            ss << " \tANGLE: " << robots[i].angle;
        }
        ss << endl << endl << "Robots Team 2:" << endl;
        for(int i = 3 ; i < 6 ; i++){
            ss << "Robot: (X: " << robots[i].position.x;
            ss << " \tY: " << robots[i].position.y;
            ss << " \tANGLE: " << robots[i].angle;
        }

        ss << endl << endl << "Ball:" << endl;
        ss << ball.position.x << " " << ball.position.y << endl;

        return ss.str();
    }

};

#endif //SDK_RODETAS_STATE_H
