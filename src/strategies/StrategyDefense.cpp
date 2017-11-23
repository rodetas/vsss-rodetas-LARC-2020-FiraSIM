#include "StrategyDefense.h"

StrategyDefense::StrategyDefense() : StrategyBase()	{
	name = "defense";
}

Command StrategyDefense::strategy(Robot robot, Command command){
	Command c = command;

	c = stopStrategy(c);

	return c;
}

void StrategyDefense::defineCommand(Command _command){
	command = _command;
}

void StrategyDefense::defineTarget(Robot robot){
	target = Point(110,65,0);
}