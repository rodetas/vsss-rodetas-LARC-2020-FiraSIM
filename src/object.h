#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

using namespace common;

class Object {

public:
    Object(){
    }

    btVector3 get_position(){
        return pose;
    }

    void set_position(btVector3 _pose){
        pose = _pose;
    }

    btVector3 get_velocity_vector(){
        return v_pose;
    }

    void set_velocity_vector(btVector3 _v_pose){
        v_pose = _v_pose;
    }

    virtual btVector3 get_projection(){
        // TODO
        return pose;
    }

    btVector3 calculate_projection(){
    /*  Point aux = Point(pose.x+radius/2, pose.y+radius/2);
        
        projection.x = aux.x + (lastPositions[0].x - lastPositions[10].x);
        projection.y = aux.y + (lastPositions[0].y - lastPositions[10].y);

        if(projection.x > image_size.x || projection.x < 0 || projection.y > image_size.y || projection.y < 0){
            projection = lastRobotProjection;
        }
            
        lastRobotProjection = projection;

        return projection; */
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
        cout << "IMPLEMENTAR" << endl;
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

    btVector3 pose;
    btVector3 v_pose;
    btVector3 projection;

protected:

};

#endif