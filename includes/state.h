#ifndef STATE_H_
#define STATE_H_

#include <common.h>
#include <robot.h>
#include <ball.h>

using namespace common;

class State {

public:
    Robot robots[6];
      
    Ball ball;

    //! Default constructor: State s;
    State() = default;

    static State Global_State2State(vss_state::Global_State global_state, string main_color);

    void show();

};

#endif