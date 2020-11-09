//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTATE_H
#define SDK_RODETAS_ROBOTSTATE_H

#include <Domain/Point.h>
#include <Helpers/MathHelper.h>
#include <cmath>
#include <Domain/RobotSpeed.h>

class RobotState {

public:

    vss::Point position;
    vss::Point projection;

    double angle;
    double angularSpeed;
    double linearSpeed;
    vss::Point vectorSpeed;
    int robotSpeed = 0;

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

    double cosFrom(vss::Point _p) {
        return cos(Math::toRadian((Math::angulation(position,_p) - angle)));
    }

    double sinFrom(vss::Point _p) {
        return sin(Math::toRadian(Math::angulation(position,_p) - angle));
    }

    double distanceFrom(vss::Point _p) {
        return Math::distancePoint(position, _p);
    }

    int getRobotSpeed() {
    return this->robotSpeed;
}

    void setRobotSpeed(int speed){
    this->robotSpeed = speed;
}


};

#endif //SDK_RODETAS_ROBOTSTATE_H
