//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_RODETASBALL_H
#define SDK_RODETAS_RODETASBALL_H

class BallState {

public:

    vss::Point position;
    vss::Point projection;
    vss::Point vectorSpeed;

    double linearSpeed;

    void setPosition(vss::Point p){
        this->position = p;
    }

    void setProjection(vss::Point p){
        this->projection = p;
    }

    void setVectorSpeed(vss::Point p){
        this->vectorSpeed = p;
    }

    void setLinearSpeed(double speed){
        this->linearSpeed = speed;
    }

    vss::Point getPosition(){
        return this->position;
    }

    double getLinearSpeed(){
        return this->linearSpeed;
    }

};

#endif //SDK_RODETAS_RODETASBALL_H
