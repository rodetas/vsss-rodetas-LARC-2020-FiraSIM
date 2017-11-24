#include "robot.h"

Robot::Robot() : Object(){
    initialize();
}

Robot::Robot(int _id) : Object(){
    initialize();
}

void Robot::initialize(){
    stoppedTime = 0;

    curveFactor = 0.4f;
    potencyFactor = 1.0f;

    pose = btVector3(0,0,0);
}

void Robot::update_robot(Robot r){
    set_position(r.pose);
    set_velocity_vector(r.v_pose);
}

void Robot::show(){
    printf("Robot: (X: %f Y: %f Z: %f Vel: %f)\n", pose.x, pose.y, pose.z, velocity);
}

bool Robot::is_parallel_goal(btVector3 image){
    return (cos_from( btVector3(image.x, y())) > -0.3 && 
            cos_from( btVector3(image.x, y())) <  0.3);
}

bool Robot::is_stopped(){
    //return stopped;
}

bool Robot::is_stopped_for(int time){
    /* if(stoppedTime >= time){
        return true;
    }

    return false; */
}

bool Robot::is_blocked(btVector3 target){
    // se a distancia pro target e alta e o robo esta parado por muito tempo, entao é considerado travado
    /* if(distance_from(target) > radius * (6) && is_stopped_for(90)){
        return true;
    }  */

    return false;
}

bool Robot::calculate_stopped(){
    /* if(velocity < 5.0){
        stoppedTime++;
        return true;
    }

    stoppedTime = 0;

    return false; */
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