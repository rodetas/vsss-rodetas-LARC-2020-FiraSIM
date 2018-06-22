//
// Created by manoel on 06/05/18.
//

#include "StateInterpreter.h"
#include <iostream>
using namespace std;
bool trocou=false;
StateInterpreter::StateInterpreter() {
    strategiesById.resize(3);
    timeLastChange = -1;
};

std::vector<MindSet> StateInterpreter::defineStrategy(std::vector<RodetasRobot>& robots,  RodetasState& state) {

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
//		double distanceGoalKeeperBall = Math::distancePoint(goalRobot.getSelfState().position, state.ball.getPosition());

		// na defesa, o mais perto é o atacante
        if(distanceDefenderBall < distanceAttackerBall &&
           state.ball.position.x < vss::MAX_COORDINATE_X/2 &&
           !attackerRobot.getRobotStrategyBase().isBlocked() &&
           !defenderRobot.getRobotStrategyBase().isBlocked()){

            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

		    if(attackerRobot.getRobotStrategyBase().isBlocked())
        {
            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }


            //Troca defensor por atacante
            if(state.ball.position.x < vss::MAX_COORDINATE_X/2 &&
              !attackerRobot.getRobotStrategyBase().isBlocked() &&
              !goalRobot.getRobotStrategyBase().isBlocked()&&
              state.ball.position.y > 35 && state.ball.position.y < 105 && state.ball.position.x < 30 &&
              ((attackerRobot.getSelfState().position.y - state.ball.position.y) > 7 ||
              (state.ball.position.y - attackerRobot.getSelfState().position.y)) > -7 && // Distancia entre atacante e bola
              ((defenderRobot.getSelfState().position.y <= 30 && attackerRobot.getSelfState().position.y >= 50) ||
              (defenderRobot.getSelfState().position.y >= 80 && attackerRobot.getSelfState().position.y <= 60)))
               {
                cout<<"trocou......................................................................!"<<endl;
                cout<<"trocou......................................................................!"<<endl;
                cout<<"trocou......................................................................!"<<endl;
                strategiesById[attackerRobot.getId()] = MindSet::Defender;
                strategiesById[defenderRobot.getId()] = MindSet::Attacker;
                //exit(1);
                //return strategiesById;
              }

//		//trocar goleiro
//		if(distanceGoalKeeperBall < distanceAttackerBall &&
//           state.ball.position.x > vss::MAX_COORDINATE_X/4 &&
//           !attackerRobot.getRobotStrategyBase().isBlocked() &&
//           !goalRobot.getRobotStrategyBase().isBlocked()){
//			strategiesById[attackerRobot.getId()] = MindSet::Defender;
//			strategiesById[defenderRobot.getId()] = MindSet::GoalKeeper;
//			strategiesById[goalRobot.getId()] = MindSet::Attacker;
//		}

        timeLastChange = 60;
    }

    if(timeLastChange >= 0) timeLastChange--;

    return strategiesById;
}

RodetasRobot StateInterpreter::getRobotByStrategy(MindSet mindSet, std::vector<RodetasRobot>& robots) {

    auto found = std::find_if(robots.begin(), robots.end(), [&](RodetasRobot r){
       return r.getMindSet() == mindSet;
    });

    return *found;
}
