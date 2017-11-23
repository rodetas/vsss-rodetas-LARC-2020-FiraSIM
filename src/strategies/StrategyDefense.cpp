#include "StrategyDefense.h"

StrategyDefense::StrategyDefense() : StrategyBase()	{
	name = "defense";
}

Command StrategyDefense::strategy(Robot robot, Command command){
	Command c = command;

	c = stop_strategy(c);

	return c;
}

void StrategyDefense::define_command(Command _command){
	command = _command;
}

void StrategyDefense::define_target(Robot robot){
	target = Point(110,65,0);
}