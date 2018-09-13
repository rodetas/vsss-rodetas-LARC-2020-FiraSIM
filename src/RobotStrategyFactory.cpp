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

			case MindSet::GoalKeeperCenterPositioning:
				if(robot.getMindSet() != MindSet::GoalKeeperCenterPositioning) {
				    robot.setMindSet(MindSet::GoalKeeperCenterPositioning);
				    robot.setStrategy(new GoalKeepCenterPositioning());
				}

			default:
				break;
		}
	}
}