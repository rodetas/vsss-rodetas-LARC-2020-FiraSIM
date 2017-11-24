#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

using namespace common;

class Object {

public:
    Object(){}

    btVector3 get_position(){
        return pose;
    }

    void set_position(btVector3 _pose){
        pose = _pose;
        projection = calculate_projection();
    }

    btVector3 get_velocity_vector(){
        return v_pose;
    }

    float get_velocity(){
        return velocity;
    }

    void set_velocity_vector(btVector3 _v_pose){
        v_pose = _v_pose;
        velocity = calculate_velocity();
    }

    btVector3 get_projection(){
        return projection;
    }

    virtual btVector3 calculate_projection(){
        btVector3 projection;
        projection.x = pose.x + v_pose.x;
        projection.y = pose.y + v_pose.y;

        return projection; 
    }

    float calculate_velocity(){
        return sqrt(pow(v_pose.x,2) + pow(v_pose.y,2));
    }

    float x(){
        return pose.x;
    }

    float y(){
        return pose.y;
    }

    float yaw(){
        return pose.z;
    }

    bool is_null(){
        return (pose.x <= 0 && pose.y <= 0);
    }

    bool is_board(btVector3 image_size){
	    return (pose.y > image_size.y * (0.90) || pose.y < image_size.y * (0.10) || 
                pose.x > image_size.x * (0.85) || pose.x < image_size.x * (0.15) );
    }

    virtual void show(){
        printf("Object: (X: %f Y: %f Z: %f)\n", pose.x, pose.y, pose.z);
    }

    float cos_from(Object _r) const{
        return cos((angulation(pose, _r.get_position()) - pose.z)/(180/M_PI));
    }

    float cos_from(btVector3 _p) const{
        return cos((angulation(pose,_p) - pose.z)/(180/M_PI));
    }

    float sin_from(Object _r) const{
        return sin((angulation(pose,_r.get_position()) - pose.z)/(180/M_PI));
    }

    float sin_from(btVector3 _p) const{
        return sin((angulation(pose,_p) - pose.z)/(180/M_PI));
    }

    float distance_from(Object _r) const{
        return distancePoint(pose, _r.get_position());
    }

    float distance_from(btVector3 _p) const{
        return distancePoint(pose, _p);
    }

protected:
    float velocity;

    btVector3 pose;
    btVector3 v_pose;
    btVector3 projection;
};

#endif