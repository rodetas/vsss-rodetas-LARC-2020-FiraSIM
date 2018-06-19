//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTATE_H
#define SDK_RODETAS_ROBOTSTATE_H

#include <Common.h>
#include <Domain/Point.h>
#include "Helpers/MathHelper.h"

class RobotState {

public:

    vss::Point position;
    vss::Point projection;

    double angle;
    double angularSpeed;
    double linearSpeed;
    vss::Point vectorSpeed;

    RobotState(){
        this->position = vss::Point(0,0);
        this->angle = 0;
        this->angularSpeed = 0;
        this->linearSpeed = 0;
        this->vectorSpeed = vss::Point();
    };

    void setPosition(vss::Point p){
        this->position = p;
    }

    void setProjection(vss::Point p){
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

    void setVectorSpeed(vss::Point speed){
        this->vectorSpeed = speed;
    }

//@TODO: tirar as contas daqui e jogar pro MathHelper, deixar apenas as chamadas
    double cosFrom(vss::Point _p) {
        return cos((Math::angulation(position,_p) - angle)/(180/M_PI));
    }

    double sinFrom(vss::Point _p) {
        return sin((Math::angulation(position,_p) - angle)/(180/M_PI));
    }

    double distanceFrom(vss::Point _p) {
        return Math::distancePoint(position, _p);
    }

};

#endif //SDK_RODETAS_ROBOTSTATE_H
