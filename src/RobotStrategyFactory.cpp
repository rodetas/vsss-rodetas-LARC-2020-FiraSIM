//
// Created by manoel on 24/04/18.
//

#include "RobotStrategyFactory.h"

RobotStrategyFactory::RobotStrategyFactory() = default;

void RobotStrategyFactory::manage(std::vector<RodetasRobot>& robots, RodetasState& state, bool swap) {

    if(swap){
	    std::vector<MindSet> strategiesById = interpreter.defineStrategy(robots, state);

    	for(RodetasRobot& robot : robots){
        	MindSet robotMindSet = strategiesById[robot.getId()];

        	switch(robotMindSet){
            	case MindSet::GoalKeeper:
                	robot.setMindSet(MindSet::GoalKeeper);
                	robot.setStrategy(new RobotStrategyGoal());
                	break;
            	case MindSet::Defender:
                	robot.setMindSet(MindSet::Defender);
                	robot.setStrategy(new RobotStrategyDefender());
                	break;
            	case MindSet::Attacker:
                	robot.setMindSet(MindSet::Attacker);
                	robot.setStrategy(new RobotStrategyAttack());
                	break;
        	}
    	}
	}
}