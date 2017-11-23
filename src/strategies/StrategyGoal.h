#ifndef STRATEGY_GOAL_H_
#define STRATEGY_GOAL_H_

#include "StrategyBase.h"

class StrategyGoal : public StrategyBase {

public:
    StrategyGoal();

    virtual Command strategy(Robot, Command);
    virtual Command stop_strategy(Command);
    virtual void define_target(Robot);
    virtual void define_command(Command);
};

#endif