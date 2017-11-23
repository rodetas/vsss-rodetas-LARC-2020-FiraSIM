#ifndef ROBOT_H_
#define ROBOT_H_

#include "common.h"
#include "ball.h"
#include "object.h"

using namespace common;

class Robot : public Object {

public:
    Robot();
    Robot(int);

    Robot& operator=(const Robot& r) {
        if (this != &r){
            pose = r.pose;
            radius = r.radius;
        }
        return *this;
    }

    void initialize();

    bool isParallelGoal(btVector3);    
    bool isStopped();
    bool isStoppedFor(int);    
    bool calculateStopped();
    bool isBlocked(btVector3);

    void setRadius(float);
    float getRadius();

    void setPotencyFactor(float);
    float getPotencyFactor();

    void setCurveFactor(float);
    float getCurveFactor();
   
    btVector3 calculateRobotProjection();

    // VARIABLES

    int stoppedTime;
    bool stopped;

    float radius;
    float potencyFactor;
    float curveFactor;
};

#endif