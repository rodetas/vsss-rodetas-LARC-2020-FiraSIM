#ifndef ROBOT_H_
#define ROBOT_H_

#include "common.h"
#include "Ball.h"

using namespace common;

class Robot {

public:
    Robot();
    Robot(int);

    Robot& operator=(const Robot& r) {
        if (this != &r){
            radius = r.radius;
            pose = r.pose;
        }
        return *this;
    }

    int y() const;
    int x() const;

    void initialize();

    /**
     * Returns if a rodetas::object is near the board
     * \param the object you want to know if is near the board
     * \return true if is near
     */
    bool isBoard();
    bool isParallelGoal();    
    bool isNull();
    bool isStopped();
    bool isStoppedFor(int);    
    bool calculateStopped();
    bool isBlocked(btVector3);

    void setRadius(float);
    float getRadius();

    void setPotencyFactor(float);
    float getPotencyFactor();

    void setCurveFactor(float);
    float getCurveFactor();

    void setPosition(btVector3);
    btVector3 getPosition() const;
   
    btVector3 getProjection();
    btVector3 calculateRobotProjection();

    float cosFrom(Robot) const;
    float cosFrom(btVector3) const;

    float sinFrom(Robot) const;
    float sinFrom(btVector3) const;

    float distanceFrom(Robot) const;
    float distanceFrom(Ball) const;
    float distanceFrom(btVector3) const;

    // VARIABLES

    btVector3 pose;
    btVector3 v_pose;
    btVector3 projection;

    int stoppedTime;
    bool stopped;

    float radius;
    float potencyFactor;
    float curveFactor;
};

#endif