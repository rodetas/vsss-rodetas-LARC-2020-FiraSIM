#include "robot.h"

Robot::Robot() : Object(){
    initialize();
}

Robot::Robot(int _id) : Object(){
    initialize();
}

void Robot::initialize(){
    stoppedTime = 0;

    radius = 5.0f;
    curveFactor = 0.4f;
    potencyFactor = 1.0f;

    pose = btVector3(0,0,0);
}

bool Robot::isParallelGoal(btVector3 image){
    return (cosFrom( btVector3(image.x, y())) > -0.3 && 
            cosFrom( btVector3(image.x, y())) <  0.3);
}

bool Robot::isStopped(){
    //return stopped;
}

bool Robot::isStoppedFor(int time){
    /* if(stoppedTime >= time){
        return true;
    }

    return false; */
}

bool Robot::isBlocked(btVector3 target){
    /* // se a distancia pro target e alta e o robo esta parado por muito tempo, entao é considerado travado
    if(distanceFrom(target) > radius * (6) && isStoppedFor(90)){
        return true;
    } 

    return false; */
}

bool Robot::calculateStopped(){
    /* if(velocity < 5.0){
        stoppedTime++;
        return true;
    }

    stoppedTime = 0;

    return false; */
}

Point Robot::calculateRobotProjection(){
   /*  Point aux = Point(pose.x+radius/2, pose.y+radius/2);
    
    projection.x = aux.x + (lastPositions[0].x - lastPositions[10].x);
    projection.y = aux.y + (lastPositions[0].y - lastPositions[10].y);

    if(projection.x > image_size.x || projection.x < 0 || projection.y > image_size.y || projection.y < 0){
        projection = lastRobotProjection;
    }
        
    lastRobotProjection = projection;

    return projection; */
}

void Robot::setPotencyFactor(float _p){
    potencyFactor = _p;
}

float Robot::getPotencyFactor(){
    return potencyFactor;
}

void Robot::setCurveFactor(float _c){
    curveFactor = _c;
}

float Robot::getCurveFactor(){
    return curveFactor;
}

void Robot::setRadius(float r){
    radius = r;
}

float Robot::getRadius(){
    return radius;
}
