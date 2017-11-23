#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

using namespace common;

class Object {

public:
    Object(){
    }

    btVector3 getPosition(){
        return pose;
    }

    void setPosition(btVector3 _pose){
        pose = _pose;
    }

    btVector3 getVelocityVector(){
        return v_pose;
    }

    void setVelocityVector(btVector3 _v_pose){
        v_pose = _v_pose;
    }

    virtual btVector3 getProjection(){
        // TODO
        return pose;
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

    bool isNull(){
        return (pose.x <= 0 && pose.y <= 0);
    }

    bool isBoard(btVector3 image_size){
	    return (pose.y > image_size.y * (0.90) || pose.y < image_size.y * (0.10) || 
                pose.x > image_size.x * (0.85) || pose.x < image_size.x * (0.15) );
    }

    virtual void show(){
        cout << "IMPLEMENTAR" << endl;
    }

    float cosFrom(Object _r) const{
        return cos((angulation(pose, _r.getPosition()) - pose.z)/(180/M_PI));
    }

    float cosFrom(btVector3 _p) const{
        return cos((angulation(pose,_p) - pose.z)/(180/M_PI));
    }

    float sinFrom(Object _r) const{
        return sin((angulation(pose,_r.getPosition()) - pose.z)/(180/M_PI));
    }

    float sinFrom(btVector3 _p) const{
        return sin((angulation(pose,_p) - pose.z)/(180/M_PI));
    }

    float distanceFrom(Object _r) const{
        return distancePoint(pose, _r.getPosition());
    }

    float distanceFrom(btVector3 _p) const{
        return distancePoint(pose, _p);
    }

    btVector3 pose;
    btVector3 v_pose;
    btVector3 projection;

protected:

};

#endif