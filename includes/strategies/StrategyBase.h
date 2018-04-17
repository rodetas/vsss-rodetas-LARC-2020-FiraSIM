#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <common.h>
#include <movimentation.h>
#include <univectorfield.h>
#include <RodetasState.h>
#include <config.h>

using namespace common;

class StrategyBase {
    
public:
    /**
     * Default constructor
     */
    StrategyBase();

    virtual Robot apply(map<string, int>, vss::State);
     
    virtual void move(map<string, int>, vss::State);

    /**
     * Pure virtual function to apply the strategy
    */
    virtual Command strategy(Robot, Command) = 0;

    /**
     * Pure virtual function to define where goes the robot
     */
    virtual btVector3 define_target(Robot) = 0;

    /**
     * Apply the robot strategy when it's on the corner
     */
    virtual Command corner_strategy(Command);

    virtual Command stop_strategy(Command);

    virtual Command blocked_strategy(Command);

    virtual Command kick_strategy(Command);

    virtual Command collision_strategy(Command);

    void set_state(map<string, int>, vss::State);

    void define_command(Command);

    Command get_command();

protected:    
    static float curve_factor;
    static float potency_factor;

    btVector3 goal_size;
    btVector3 image_size;
    btVector3 goal_center_position;
    btVector3 goal_area_size;

    string name;
    string side;

    Robot robot;
//    Point target;
    RodetasState state;
    map<string, int> id;

    Command command;
    Movimentation* movimentation;

    Robot get_robot(string);

};

#endif