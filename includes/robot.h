#ifndef ROBOT_H_
#define ROBOT_H_

#include <common.h>
#include <ball.h>
#include <object.h>

using namespace common;

class Robot : public Object {

public:
    Robot();
    explicit Robot(int);

    string show() override;

    void initialize();
    void update_robot(Robot);
    void calculate_stopped();

    bool is_stopped();
    bool is_blocked(btVector3);
    bool is_stopped_for(int);
    bool is_parallel_goal(btVector3);    

    void set_target(btVector3 _t);
    void set_curve_factor(float);
    void set_potency_factor(float);
    void set_potencial_direction(btVector3);

    btVector3 get_target();
    float get_curve_factor();
    float get_potency_factor();
    btVector3 get_potencial_direction();

    Path path;

private:
    int stopped_frames;
    bool stopped;

    float potencyFactor;
    float curveFactor;

    btVector3 target;
    btVector3 potencial_direction;
};

#endif