#include "StrategyDefense.h"

StrategyDefense::StrategyDefense() : StrategyBase()	{
	name = "defense";
}

Command StrategyDefense::strategy(Robot robot, Command command){
	Command c = command;

	c = stop_strategy(c);

	return c;
}

btVector3 StrategyDefense::define_target(Robot robot){
	return Point(110,65,0);
}