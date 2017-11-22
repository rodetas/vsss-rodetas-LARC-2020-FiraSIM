#ifndef ROBOT_H_
#define ROBOT_H_

#include "common.h"
#include "Ball.h"

using namespace common;

class Robot {

public:
    Robot();
    Robot(int);

    Robot(int _id, int _x, int _y);

    Robot& operator=(const Robot& r) {
        
        if (this != &r){
            id = r.id;
            radius = r.radius;
            pose = r.pose;
            target = r.target;
            velocity = r.velocity;
            angle = r.angle;
            command = r.command;
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

    bool calculateStopped();
    bool isStopped();
    bool isStoppedFor(int);
    
    bool isBlocked();

    float getVelocity();

    void setRobotId(int);
    int getId();

    void setPotencyFactor(float);
    float getPotencyFactor();

    void setCurveFactor(float);
    float getCurveFactor();

    void setPosition(btVector3);
    btVector3 getPosition() const;

    void setAngle(float);
    float getAngle() const;

    void setRadius(float);
    float getRadius();

    void setCommand(Command);
    Command getCommand();

    Command getLastCommand();

    void setTarget(btVector3);
    btVector3 getTarget() const;

    void setLastPositions(vector<btVector3>);
    vector<btVector3>::iterator getLastPositionsBegin();
    vector<btVector3>::iterator getLastPositionsEnd();

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

    btVector3 v_pose;

    const int velocityPrecision = 10;

    int id;
    int stoppedTime;

    float velocity;
    float angle;
    float radius;

    float potencyFactor;
    float curveFactor;

    bool stopped;

    btVector3 pose;
    btVector3 target;

    Command command;
    Command lastCommand;

    btVector3 projection;
};

#endif