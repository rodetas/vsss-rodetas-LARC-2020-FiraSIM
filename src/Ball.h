#ifndef BALL_H_
#define BALL_H_

#include "common.h"

class Ball {

public:
    common::btVector3 pose;
    common::btVector3 v_ball;

    common::btVector3 getPosition(){
        return pose;
    }

};

#endif