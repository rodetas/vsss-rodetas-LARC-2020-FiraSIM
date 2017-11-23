#ifndef ATTACK_STRATEGY_H_
#define ATTACK_STRATEGY_H_

#include "StrategyBase.h"

class StrategyAttack : public StrategyBase {

public:
    StrategyAttack();

    virtual Command strategy(Robot, Command);
    virtual Command kick_strategy(Command);
    virtual void define_target(Robot);
    virtual void define_command(Command);
};

#endif