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

    //Troca defensor por atacante
    cout<<"ballx "<<state.ball.position.x<<" y comp "<<vss::MAX_COORDINATE_Y/2+40<<endl;
    cout<<"bally "<<state.ball.position.y<<" y comp "<<vss::MAX_COORDINATE_Y/2+40<<endl;
    cout<<"vss::MAX_COORDINATE_X/2"<<vss::MAX_COORDINATE_X/2<<endl;
    if(state.ball.position.x < vss::MAX_COORDINATE_X/2 &&
       state.ball.position.y > 40 && //metade do campo + 20 cm
       state.ball.position.y < 90 && state.ball.position.x < 25 &&
       !attackerRobot.getRobotStrategyBase().isBlocked() &&
       !defenderRobot.getRobotStrategyBase().isBlocked())
       //!(attackerRobot.getSelfState().position.y > 25 && attackerRobot.getSelfState().position.y < 105 && // se nao tiver ambos dentro da area
       //!defenderRobot.getSelfState().position.y>25 && defenderRobot.getSelfState().position.y < 105&&      //realiza troca
       //defenderRobot.getSelfState().position.x >= vss::MAX_COORDINATE_X * 0.2))
    {
        cout<<"trocou......................................................................!"<<endl;
        cout<<"trocou......................................................................!"<<endl;
        cout<<"trocou......................................................................!"<<endl;
        strategiesById[attackerRobot.getId()] = MindSet::Defender;
        strategiesById[defenderRobot.getId()] = MindSet::Attacker;
}
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
