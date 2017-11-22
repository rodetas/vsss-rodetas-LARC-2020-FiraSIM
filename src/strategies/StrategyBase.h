#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include "../common.h"
#include "../Movimentation.h"

enum {PARADO, DEFENDENDO, ATACANDO};

class Strategy;

using namespace common;

class StrategyBase {
    
public:
    /**
     * Default constructor
     */
    StrategyBase();

    virtual void apply(string, map<string, int>, State);
     
    virtual void move(Robot);

    /**
     * Pure virtual function to apply the strategy
    */
    virtual Command strategy(Robot, Command) = 0;

    /**
     * Pure virtual function to define where goes the robot
     */
    virtual void defineTarget(Robot) = 0;

    /**
     * Pure virtual function to define the final pwm
     */
    virtual void defineCommand(Command) = 0;
    
    /**
     * Apply the robot strategy when it's on the corner
     */
    virtual Command cornerStrategy(Command);

    virtual Command stopStrategy(Command);

    virtual Command blockedStrategy(Command);

    virtual Command kickStrategy(Command);

    virtual Command collisionStrategy(Command);

    void setRobot(Robot);

    void setState(State);

protected:    
    static float curve_factor;
    static float potency_factor;

    int robotState; ///< for represent the atual robot state (PARADO, DEFENDENDO, ATACANDO)

    Robot robot;
    Point target;
    State position;
    Command command;
    Movimentation movimentation;  
};

#endif