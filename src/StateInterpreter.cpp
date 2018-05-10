//
// Created by manoel on 06/05/18.
//

#include "StateInterpreter.h"

//@TODO: tirar imageSize daqui
btVector3 imageSize = {170,130};

StateInterpreter::StateInterpreter() {
    strategiesById.resize(3);
    timeLastChange = -1;
};

vector<MindSet> StateInterpreter::defineStrategy(vector<RodetasRobot>& robots,  RodetasState& state) {

    RodetasRobot goalRobot = getRobotByStrategy(MindSet::GoalKeeper, robots);
    RodetasRobot defenderRobot = getRobotByStrategy(MindSet::Defender, robots);
    RodetasRobot attackerRobot = getRobotByStrategy(MindSet::Attacker, robots);

    strategiesById[goalRobot.getId()] = goalRobot.getMindSet();
    strategiesById[defenderRobot.getId()] = defenderRobot.getMindSet();
    strategiesById[attackerRobot.getId()] = attackerRobot.getMindSet();

    if(timeLastChange == -1){

        if (attackerRobot.getSelfState().position.x*1.3 < state.ball.position.x &&
                !(attackerRobot.getSelfState().position.x < state.ball.position.x &&
                defenderRobot.getSelfState().position.x < state.ball.position.x) &&
            !attackerRobot.getRobotStrategyBase().isBlocked() &&
            !defenderRobot.getRobotStrategyBase().isBlocked()){

                strategiesById[attackerRobot.getId()] = MindSet::Defender;
                strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

		double distanceDefenderBall = Math::distancePoint(defenderRobot.getSelfState().position, state.ball.getPosition());
        double distanceAttackerBall = Math::distancePoint(attackerRobot.getSelfState().position, state.ball.getPosition());

		// na defesa, o mais perto é o atacante
        if(distanceDefenderBall < distanceAttackerBall &&
           state.ball.position.x < imageSize.x/2 &&
           !attackerRobot.getRobotStrategyBase().isBlocked() &&
           !defenderRobot.getRobotStrategyBase().isBlocked()){

            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

		if(attackerRobot.getRobotStrategyBase().isBlocked()){
            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

        timeLastChange = 60;
    }

    if(timeLastChange >= 0) timeLastChange--;

    return strategiesById;
}

RodetasRobot StateInterpreter::getRobotByStrategy(MindSet mindSet, vector<RodetasRobot>& robots) {

    auto found = std::find_if(robots.begin(), robots.end(), [&](RodetasRobot r){
       return r.getMindSet() == mindSet;
    });

    return *found;
}