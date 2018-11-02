//
// Created by manoel on 24/04/18.
//

#include "RobotStrategyFactory.h"

RobotStrategyFactory::RobotStrategyFactory() = default;

void RobotStrategyFactory::manage(std::vector<RodetasRobot>& robots, RodetasState& state, bool enabledSwap, bool isFreeBall, PositionStatus positionStatus) {

	// funcao retorna um vetor contendo no indice 0 o mindSet do Robo 0, no indice 1 mindSet do robo 1, etc
	std::vector<MindSet> mindSetById = interpreter.manageStrategyOrPositioning(robots, state, enabledSwap, isFreeBall, positionStatus );

	std::cout << "MINDSET" << std::endl;
	for(auto i : mindSetById){
		std::cout << toString(i) << std::endl;
	}
	std::cout << std::endl;

	constructStrategies(robots, mindSetById);

}

// funcao que insere para cada robo o Agente que foi escolhido para ele
void RobotStrategyFactory::constructStrategies(std::vector<RodetasRobot>& robots, std::vector<MindSet>& mindSetById) {

	for (RodetasRobot &robot : robots) {
		MindSet robotMindSet = mindSetById[robot.getId()];

		switch (robotMindSet) {
			case MindSet::GoalKeeperStrategy:
				if (robot.getMindSet() != MindSet::GoalKeeperStrategy) {
					robot.setMindSet(MindSet::GoalKeeperStrategy);
					robot.setStrategy(new RobotStrategyGoal());
				}
				break;
			case MindSet::DefenderStrategy:
				if (robot.getMindSet() != MindSet::DefenderStrategy) {
					robot.setMindSet(MindSet::DefenderStrategy);
					robot.setStrategy(new RobotStrategyDefender());
				}
				break;
			case MindSet::AttackerStrategy:
				if (robot.getMindSet() != MindSet::AttackerStrategy) {
					robot.setMindSet(MindSet::AttackerStrategy);
					robot.setStrategy(new RobotStrategyAttack());
				}
				break;

			case MindSet::PenaltyHitAttackPositioning:
				if (robot.getMindSet() != MindSet::PenaltyHitAttackPositioning) {
					robot.setMindSet(MindSet::PenaltyHitAttackPositioning);
					robot.setStrategy(new AttackPenaltyHitPositioning());
				}
				break;
			case MindSet::PenaltyHitDefenderPositioning:
				if (robot.getMindSet() != MindSet::PenaltyHitDefenderPositioning) {
					robot.setMindSet(MindSet::PenaltyHitDefenderPositioning);
					robot.setStrategy(new DefenderPenaltyHitPositioning());
				}
				break;
			case MindSet::PenaltyAgainstAttackPositioning:
				if (robot.getMindSet() != MindSet::PenaltyAgainstAttackPositioning) {
					robot.setMindSet(MindSet::PenaltyAgainstAttackPositioning);
					robot.setStrategy(new AttackPenaltyAgainstPositioning());
				}
				break;

			case MindSet::PenaltyAgainstDefenderPositioning:
				if (robot.getMindSet() != MindSet::PenaltyAgainstDefenderPositioning) {
					robot.setMindSet(MindSet::PenaltyAgainstDefenderPositioning);
					robot.setStrategy(new DefenderPenaltyAgainstPositioning());
				}
				break;

			case MindSet::DefenderMiddleDefensePositioning:
				if (robot.getMindSet() != MindSet::DefenderMiddleDefensePositioning) {
					robot.setMindSet(MindSet::DefenderMiddleDefensePositioning);
					robot.setStrategy(new DefenderMiddleDefensePositioning());
				}
				break;
			
			case MindSet::AttackMiddleDefensePositioning:
				if (robot.getMindSet() != MindSet::AttackMiddleDefensePositioning) {
					robot.setMindSet(MindSet::AttackMiddleDefensePositioning);
					robot.setStrategy(new AttackMiddleDefensePositioning());
				}
				break;
			
			case MindSet::DefenderMiddleAttackPositioning:
				if (robot.getMindSet() != MindSet::DefenderMiddleAttackPositioning) {
					robot.setMindSet(MindSet::DefenderMiddleAttackPositioning);
					robot.setStrategy(new DefenderMiddleAttackPositioning());
				}
				break;

			case MindSet::AttackMiddleAttackPositioning:
				if (robot.getMindSet() != MindSet::AttackMiddleAttackPositioning) {
					robot.setMindSet(MindSet::AttackMiddleAttackPositioning);
					robot.setStrategy(new AttackMiddleAttackPositioning());
				}
				break;

			case MindSet::AttackFreeballLeftAttackPositioning:
				if (robot.getMindSet() != MindSet::AttackFreeballLeftAttackPositioning) {
					robot.setMindSet(MindSet::AttackFreeballLeftAttackPositioning);
					robot.setStrategy(new AttackFreeballLeftAttackPositioning());
				}
				break;

			case MindSet::AttackFreeballLeftDefensePositioning:
				if (robot.getMindSet() != MindSet::AttackFreeballLeftDefensePositioning) {
					robot.setMindSet(MindSet::AttackFreeballLeftDefensePositioning);
					robot.setStrategy(new AttackFreeballLeftDefensePositioning());
				}
				break;

			case MindSet::AttackFreeballRightAttackPositioning:
				if (robot.getMindSet() != MindSet::AttackFreeballRightAttackPositioning) {
					robot.setMindSet(MindSet::AttackFreeballRightAttackPositioning);
					robot.setStrategy(new AttackFreeballRightAttackPositioning());
				}
				break;

			case MindSet::AttackFreeballRightDefensePositioning:
				if (robot.getMindSet() != MindSet::AttackFreeballRightDefensePositioning) {
					robot.setMindSet(MindSet::AttackFreeballRightDefensePositioning);
					robot.setStrategy(new AttackFreeballRightDefensePositioning());
				}
				break;

			case MindSet::GoalKeeperCenterPositioning:
				if(robot.getMindSet() != MindSet::GoalKeeperCenterPositioning) {
					robot.setMindSet(MindSet::GoalKeeperCenterPositioning);
					robot.setStrategy(new GoalKeepCenterPositioning());
				}
				break;

			case MindSet::DefenderStrategyLeft:
				if (robot.getMindSet() != MindSet::DefenderStrategyLeft) {
					robot.setMindSet(MindSet::DefenderStrategyLeft);
					robot.setStrategy(new RobotStrategyDefenderLeft());
				}
				break;

			case MindSet::DefenderStrategyRight:
				if (robot.getMindSet() != MindSet::DefenderStrategyRight) {
					robot.setMindSet(MindSet::DefenderStrategyRight);
					robot.setStrategy(new RobotStrategyDefenderRight());
				}
                break;
            case MindSet::AttackDefenseStrategy:
                if (robot.getMindSet() != MindSet::AttackDefenseStrategy) {
                    robot.setMindSet(MindSet::AttackDefenseStrategy);
                    robot.setStrategy(new RobotStrategyAttackDefense());
                }
                break;
			case MindSet::SingleAttackerStrategy:
				if (robot.getMindSet() != MindSet::SingleAttackerStrategy) {
					robot.setMindSet(MindSet::SingleAttackerStrategy);
					robot.setStrategy(new RobotStrategySingleAttack());
				}
				break;
		    case MindSet::None:
		        if (robot.getMindSet() != MindSet::None){
		            robot.setMindSet(MindSet::None);
		            robot.setStrategy(new NoneStrategy());
		        }
				break;
			default:
				std::cout << "MindSet \"" << toString(robotMindSet) << "\" nao tratado. Tente adicionar no switch" << std::endl;
				break;
		}
	}
}