#ifndef ATTACK_STRATEGY_H_
#define ATTACK_STRATEGY_H_

#include "StrategyBase.h"

class StrategyAttack : public StrategyBase {

public:
    StrategyAttack();

    virtual Command strategy(Robot, Command);
    virtual Command kickStrategy(Command);
    virtual void defineTarget(Robot);
    virtual void defineCommand(Command);
};

#endif