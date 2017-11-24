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

    virtual void show();

    void initialize();
    void update_robot(Robot);

    bool is_stopped();
    bool is_blocked(btVector3);
    bool is_stopped_for(int);    
    bool is_parallel_goal(btVector3);    
    bool calculate_stopped();

    void set_target(btVector3 _t);
    void set_curve_factor(float);
    void set_potency_factor(float);

    btVector3 get_target();
    float get_curve_factor();
    float get_potency_factor();

private:
    int stoppedTime;
    bool stopped;

    float potencyFactor;
    float curveFactor;

    btVector3 target;
};

#endif