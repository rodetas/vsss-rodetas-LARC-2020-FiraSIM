//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_RODETASBALL_H
#define SDK_RODETAS_RODETASBALL_H

#include <common.h>

class BallState {

public:

    common::btVector3 position;
    double linearSpeed;

    void setPosition(common::btVector3 p){
        this->position = p;
    }

    void setLinearSpeed(double speed){
        this->linearSpeed = speed;
    }

    common::btVector3 getPosition(){
        return this->position;
    }

    double getLinearSpeed(){
        return this->linearSpeed;
    }

};

#endif //SDK_RODETAS_RODETASBALL_H
