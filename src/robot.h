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

    bool is_parallel_goal(btVector3);    
    bool is_stopped();
    bool is_stopped_for(int);    
    bool calculate_stopped();
    bool is_blocked(btVector3);

    void set_radius(float);
    float get_radius();

    void set_potency_factor(float);
    float get_potency_factor();

    void set_curve_factor(float);
    float get_curve_factor();

    // VARIABLES

    int stoppedTime;
    bool stopped;

    float radius;
    float potencyFactor;
    float curveFactor;
};

#endif