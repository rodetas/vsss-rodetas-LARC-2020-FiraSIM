//
// Created by manoel on 24/04/18.
//

#include "RobotStrategyFactory.h"

RobotStrategyFactory::RobotStrategyFactory() = default;

void RobotStrategyFactory::manage(std::vector<RodetasRobot>& robots, RodetasState& state, bool enabledSwap, bool isFreeBall, PositionStatus positionStatus) {

	if(positionStatus == PositionStatus::None){
		// apenas troca se houverem 3 robos
		if (enabledSwap and robots.size() == 3) {
			manageStrategies(robots, state, isFreeBall);
		}
	} else {
		managePositioning(robots, state, positionStatus);
	}
}

void RobotStrategyFactory::manageStrategies(std::vector<RodetasRobot>& robots, RodetasState& state, bool isFreeBall){

	// retorna na posicao 0 o MindSet pro Robo 0 - retorna na posicao 1 o MindSet pro Robo 1 ...
	std::vector<MindSet> strategiesById = interpreter.defineStrategy(robots, state, isFreeBall);

	for (RodetasRobot &robot : robots) {
		MindSet robotMindSet = strategiesById[robot.getId()];

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
			default:
				break;
		}
	}
}

void RobotStrategyFactory::managePositioning(std::vector<RodetasRobot>& robots, RodetasState& state, PositionStatus positionStatus) {

//	std::vector<PositionStatus> positionsById = interpreter.definePositions(robots, state, positionStatus);
//		PositionStatus robotPositioning = positionsById[robot.getId()];


	if(positionStatus == PositionStatus::Penalty){

		if(robots[0].getMindSet() != MindSet::PenaltyAttackPositioning){
			robots[0].setMindSet(MindSet::PenaltyAttackPositioning);
			robots[0].setStrategy(new AttackPenaltyPositioning());
		}

		// @TODO posicionamento de penalti para o defensor e goleiro
//		if(robots[1].getPositionStatus() == PositionStatus::None){
//			robots[1].setMindSet(MindSet::None);
//			robots[1].setStrategy(new DefenderPenaltyPositioning());
//		}
	}

	if(positionStatus == PositionStatus::Freeball){
		// @TODO implementar posicionamentos para freeball
	}

}