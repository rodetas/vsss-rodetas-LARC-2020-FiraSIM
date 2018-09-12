//
// Created by manoel on 24/04/18.
//

#include "RobotStrategyFactory.h"

RobotStrategyFactory::RobotStrategyFactory() = default;

void RobotStrategyFactory::manage(std::vector<RodetasRobot>& robots, RodetasState& state, bool enabledSwap, bool isFreeBall, PositionStatus positionStatus) {

	std::vector<MindSet> mindSetById = interpreter.manageStrategyOrPositioning(robots, state, enabledSwap, isFreeBall, positionStatus );
	constructStrategies(robots, mindSetById);

}

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

			case MindSet::PenaltyAttackPositioning:
				if (robot.getMindSet() != MindSet::PenaltyAttackPositioning) {
					robot.setMindSet(MindSet::PenaltyAttackPositioning);
					robot.setStrategy(new AttackPenaltyPositioning());
				}
				break;
			case MindSet::PenaltyDefenderPositioning:
				if (robot.getMindSet() != MindSet::PenaltyDefenderPositioning) {
					robot.setMindSet(MindSet::PenaltyDefenderPositioning);
					robot.setStrategy(new DefenderPenaltyPositioning());
				}
				break;

			case MindSet::GoalKeeperCenterPositioning:
				break;

			default:
				break;
		}
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

//    if(lastPositionStatus != positionStatus) {
        std::cout << "ENTROU" << std::endl;
        std::vector<MindSet> positionsById = interpreter.definePositioning(robots, state, positionStatus);

        for (RodetasRobot &robot : robots) {
            MindSet robotMindSet = positionsById[robot.getId()];

            switch (robotMindSet) {

                case MindSet::PenaltyAttackPositioning:
                    if (robot.getMindSet() != MindSet::PenaltyAttackPositioning) {
                        robot.setMindSet(MindSet::PenaltyAttackPositioning);
                        robot.setStrategy(new AttackPenaltyPositioning());
                    }
                    break;

                case MindSet::PenaltyDefenderPositioning:
                    if (robot.getMindSet() != MindSet::PenaltyDefenderPositioning) {
                        robot.setMindSet(MindSet::PenaltyDefenderPositioning);
                        robot.setStrategy(new DefenderPenaltyPositioning());
                    }
                    break;

                case MindSet::GoalKeeperCenterPositioning:
                    break;

                default:
                    break;

            }
        }

//        if (positionStatus == PositionStatus::Penalty) {
//
//            if (robots[0].getMindSet() != MindSet::PenaltyAttackPositioning) {
//                robots[0].setMindSet(MindSet::PenaltyAttackPositioning);
//                robots[0].setStrategy(new AttackPenaltyPositioning());
//            }
//
//            // @TODO posicionamento de penalti para o defensor e goleiro
//            //		if(robots[1].getPositionStatus() == PositionStatus::None){
//            //			robots[1].setMindSet(MindSet::None);
//            //			robots[1].setStrategy(new DefenderPenaltyPositioning());
//            //		}
//        }
//
//        if (positionStatus == PositionStatus::Freeball) {
//            // @TODO implementar posicionamentos para freeball
//        }
//    }

}