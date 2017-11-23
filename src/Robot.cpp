#include "Robot.h"

Robot::Robot(){
    initialize();
}

Robot::Robot(int _id){
    initialize();
}

void Robot::initialize(){
    stoppedTime = 0;

    curveFactor = 0.4f;
    potencyFactor = 1.0f;

    pose = btVector3(0,0,0);
}

bool Robot::isNull(){
    /* return (pose.x <= 0 && pose.y <= 0); */
}

bool Robot::isBoard(){
    /* btVector3 imageSize = btVector3(640,480,0);
	return (pose.y > (imageSize.y*0.9) || pose.y < (imageSize.y*0.10) || 
          ((pose.x > (imageSize.x*0.85) || pose.x < (imageSize.x*0.15)))); */
}

bool Robot::isParallelGoal(){
    /* return (cosFrom(Point(imageSize.x, y())) > -0.3 && cosFrom(Point(imageSize.x, y())) < 0.3); */
}

bool Robot::isStopped(){
    /* return stopped; */
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

    if(projection.x > imageSize.x || projection.x < 0 || projection.y > imageSize.y || projection.y < 0){
        projection = lastRobotProjection;
    }
        
    lastRobotProjection = projection;

    return projection; */
}

int Robot::y() const{
    return pose.y;
}

int Robot::x() const{
    return pose.x;
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

void Robot::setPosition(btVector3 _pos){
    pose = _pos;

    stopped = calculateStopped();
    projection = calculateRobotProjection();
}

Point Robot::getPosition() const {
    return pose;
}

void Robot::setRadius(float r){
    radius = r;
}

float Robot::getRadius(){
    return radius;
}

Point Robot::getProjection(){
    return projection;
}

float Robot::cosFrom(Robot _r) const{
    return cos((angulation(pose, _r.getPosition()) - pose.z)/(180/M_PI));
}

float Robot::cosFrom(Point _p) const{
    return cos((angulation(pose,_p) - pose.z)/(180/M_PI));
}

float Robot::sinFrom(Robot _r) const{
    return sin((angulation(pose,_r.getPosition()) - pose.z)/(180/M_PI));
}

float Robot::sinFrom(Point _p) const{
    return sin((angulation(pose,_p) - pose.z)/(180/M_PI));
}

float Robot::distanceFrom(Robot _r) const{
    return distancePoint(pose, _r.getPosition());
}

float Robot::distanceFrom(Ball _b) const{
    return distancePoint(pose, _b.getPosition());
}

float Robot::distanceFrom(Point _p) const{
    return distancePoint(pose, _p);
}