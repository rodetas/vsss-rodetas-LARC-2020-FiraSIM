//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTATE_H
#define SDK_RODETAS_ROBOTSTATE_H

#include <common.h>

class RobotState {

public:

    btVector3 position;

    double angle;
    double angleSpeed;

    double linearSpeed;

    void setPosition(btVector3 p){
        this->position = p;
    }

    void setAngle(double angle){
        this->angle = angle;
    }

    void setAngleSpeed(double speed){
        this->angleSpeed = speed;
    }

    void setLinearSpeed(double speed){
        this->linearSpeed = speed;
    }

};

#endif //SDK_RODETAS_ROBOTSTATE_H
