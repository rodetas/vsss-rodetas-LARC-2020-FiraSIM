//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTATE_H
#define SDK_RODETAS_ROBOTSTATE_H

#include <common.h>
#include "MathHelper.h"

class RobotState {

public:

    common::btVector3 position;
    common::btVector3 projection;

    double angle;
    double angularSpeed;
    double linearSpeed;

    RobotState(){
        this->position = common::btVector3(0,0,0);
        this->angle = 0;
        this->angularSpeed = 0;
        this->linearSpeed = 0;
    };

    void setPosition(common::btVector3 p){
        this->position = p;
    }

    void setProjection(common::btVector3 p){
        this->projection = p;
    }

    void setAngle(double angle){
        this->angle = angle;
    }

    void setAngularSpeed(double speed){
        this->angularSpeed = speed;
    }

    void setLinearSpeed(double speed){
        this->linearSpeed = speed;
    }

//@TODO: tirar as contas daqui e jogar pro MathHelper, deixar apenas as chamadas
    double cosFrom(common::btVector3 _p) {
        return cos((Math::angulation(position,_p) - angle)/(180/M_PI));
    }

    double sinFrom(common::btVector3 _p) {
        return sin((Math::angulation(position,_p) - angle)/(180/M_PI));
    }

    double distanceFrom(common::btVector3 _p) {
        return Math::distancePoint(position, _p);
    }

};

#endif //SDK_RODETAS_ROBOTSTATE_H
