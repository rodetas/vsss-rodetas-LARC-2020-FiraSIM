//
// Created by manoel on 06/05/18.
//

#include "StateInterpreter.h"

StateInterpreter::StateInterpreter() {
    strategiesById.resize(3);
};

std::vector<MindSet>
StateInterpreter::defineStrategy(std::vector<RodetasRobot> &robots, RodetasState &state, bool freeBall) {

    RodetasRobot goalRobot = getRobotByStrategy(MindSet::GoalKeeper, robots);
    RodetasRobot defenderRobot = getRobotByStrategy(MindSet::Defender, robots);
    RodetasRobot attackerRobot = getRobotByStrategy(MindSet::Attacker, robots);

    strategiesById[goalRobot.getId()] = goalRobot.getMindSet();
    strategiesById[defenderRobot.getId()] = defenderRobot.getMindSet();
    strategiesById[attackerRobot.getId()] = attackerRobot.getMindSet();

    //Troca defensor por atacante
    if (state.ball.position.x < vss::MAX_COORDINATE_X / 2 &&
        ((state.ball.projection.y > 50 && state.ball.projection.y < 80 &&
          state.ball.position.x < defenderRobot.getSelfState().position.x)) && // Bola dentro da area
        (attackerRobot.getSelfState().position.y > 90 || attackerRobot.getSelfState().position.y < 35) &&
        (defenderRobot.getSelfState().position.y > 55) &&
        (defenderRobot.getSelfState().position.y < 75)) // se o defensor esta posicionado
    {
        strategiesById[attackerRobot.getId()] = MindSet::Defender;
        strategiesById[defenderRobot.getId()] = MindSet::Attacker;
    }

    if (freeBall) {
        // se o defensor estiver mais perto da bola entao ele passa a ser o atacante para cobrar free ball
        double distanceDefenderBall = Math::distancePoint(defenderRobot.getSelfState().position, state.ball.position);
        double distanceAttackerBall = Math::distancePoint(attackerRobot.getSelfState().position, state.ball.position);
        if (distanceDefenderBall < distanceAttackerBall) {
            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

        timeHelper.restartCounting();

    } else if (timeHelper.timeOut(2000)) {

        if (attackerRobot.getSelfState().position.x * 1.2 < state.ball.position.x &&
            !(attackerRobot.getSelfState().position.x < state.ball.position.x &&
              defenderRobot.getSelfState().position.x < state.ball.position.x) &&
            !attackerRobot.getRobotStrategyBase().isBlocked() &&
            !defenderRobot.getRobotStrategyBase().isBlocked()) {

            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

        if (attackerRobot.getRobotStrategyBase().isBlocked()) {
            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }

        /*
        //Troca defensor por atacante pelos lados do campo
        cout << "pos Defender: x: " << defenderRobot.getSelfState().position.x << endl << " y "
             << defenderRobot.getSelfState().position.y << endl;
        cout << "ball y" << state.ball.position.y << endl;
        if (state.ball.position.x < vss::MAX_COORDINATE_X / 2 &&
            //!attackerRobot.getRobotStrategyBase().isBlocked() &&
            //!defenderRobot.getRobotStrategyBase().isBlocked()&&
            ((state.ball.projection.y > 40 && state.ball.projection.y < 80) || (state.ball.position.y > 40 && state.ball.position.y < 80)) &&
            state.ball.position.x < 30 &&
            (((attackerRobot.getSelfState().position.y - state.ball.position.y) > 5 ||
              (state.ball.position.y - attackerRobot.getSelfState().position.y)) > -5 &&
            //(defenderRobot.getSelfState().position.x - state.ball.position.x > 5)&&
             ((defenderRobot.getSelfState().position.y <= 45)||
              (defenderRobot.getSelfState().position.y >= 85))))
            //((defenderRobot.getSelfState().position.y <= 30 && attackerRobot.getSelfState().position.y >= 50) ||
            //(defenderRobot.getSelfState().position.y >= 80 && attackerRobot.getSelfState().position.y <= 60)))
        {
            cout << "trocou......................................................................!" << endl;
            cout << "trocou......................................................................!" << endl;
            cout << "trocou......................................................................!" << endl;
            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
            //exit(1);
            //return strategiesById;
        }
        */

        //		//trocar goleiro
        //		if(distanceGoalKeeperBall < distanceAttackerBall &&
        //           state.ball.position.x > vss::MAX_COORDINATE_X/4 &&
        //           !attackerRobot.getRobotStrategyBase().isBlocked() &&
        //           !goalRobot.getRobotStrategyBase().isBlocked()){
        //			strategiesById[attackerRobot.getId()] = MindSet::Defender;
        //			strategiesById[defenderRobot.getId()] = MindSet::GoalKeeper;
        //			strategiesById[goalRobot.getId()] = MindSet::Attacker;
        //		}

        double distanceDefenderBall = Math::distancePoint(defenderRobot.getSelfState().position,
                                                          state.ball.getPosition());
        double distanceAttackerBall = Math::distancePoint(attackerRobot.getSelfState().position,
                                                          state.ball.getPosition());
//		double distanceGoalKeeperBall = Math::distancePoint(goalRobot.getSelfState().position, state.ball.getPosition());

        // na defesa, o mais perto é o atacante
        if (distanceDefenderBall < distanceAttackerBall &&
            state.ball.position.x < vss::MAX_COORDINATE_X * 0.5 &&
            !attackerRobot.getRobotStrategyBase().isBlocked() &&
            !defenderRobot.getRobotStrategyBase().isBlocked()) {

            strategiesById[attackerRobot.getId()] = MindSet::Defender;
            strategiesById[defenderRobot.getId()] = MindSet::Attacker;
        }
    }
    return strategiesById;
}

RodetasRobot StateInterpreter::getRobotByStrategy(MindSet mindSet, std::vector<RodetasRobot> &robots) {

    auto found = std::find_if(robots.begin(), robots.end(), [&](RodetasRobot r) {
        return r.getMindSet() == mindSet;
    });

    return *found;
}
