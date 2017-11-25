#include "robot.h"

Robot::Robot() : Object(){
    initialize();
}

Robot::Robot(int _id) : Object(){
    initialize();
}

void Robot::initialize(){
    stopped_frames = 0;

    curveFactor = 0.4f;
    potencyFactor = 1.0f;

    pose = btVector3(0,0,0);
}

void Robot::update_robot(Robot r){
    set_position(r.pose);
    set_velocity_vector(r.v_pose);
    calculate_stopped();
}

void Robot::calculate_stopped(){
    if (velocity < (6)) stopped_frames++;
    else stopped_frames = 0;
}

string Robot::show(){
    stringstream ss;
    ss << "Robot: (X: " << pose.x;
    ss << " \tY: " << pose.y;
    ss << " \tZ: " << pose.z;
    ss << " \t" << velocity << ")";
    return ss.str();
}

bool Robot::is_stopped(){
    if (stopped_frames < 6) return true;
    return false;
}

bool Robot::is_stopped_for(int time){
    if (stopped_frames >= time) return true;
    return false;
}

bool Robot::is_blocked(btVector3 target){
    if (distance_from(target) > (24) && is_stopped_for(90)) return true;
    return false;
}

bool Robot::is_parallel_goal(btVector3 image){
    return (cos_from( btVector3(image.x, y())) > -0.3 && 
            cos_from( btVector3(image.x, y())) <  0.3);
}

void Robot::set_potency_factor(float _p){
    potencyFactor = _p;
}

float Robot::get_potency_factor(){
    return potencyFactor;
}

void Robot::set_curve_factor(float _c){
    curveFactor = _c;
}

float Robot::get_curve_factor(){
    return curveFactor;
}

void Robot::set_target(btVector3 _t){
    target = _t;
}

btVector3 Robot::get_target(){
    return target;
}