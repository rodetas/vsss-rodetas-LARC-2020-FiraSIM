//
// Created by manoel on 06/05/18.
//

#include "StateInterpreter.h"

StateInterpreter::StateInterpreter() {
    lastPosStatus = PositionStatus::None;
    strategiesById.resize(3);
};

std::vector<MindSet> StateInterpreter::manageStrategyOrPositioning(std::vector<RodetasRobot> &robots, RodetasState &state, bool enabledSwap, bool freeBall, PositionStatus posStatus){

    if(posStatus == PositionStatus::None){
        if(timeAfterPositioning.getElapsedTime() < 2000){
            defineStandartStrategies(robots, state);
        } else if(enabledSwap) {
            defineStrategy(robots, state, freeBall);
        }
    } else {
        // previne que fique trocando de robo em um mesmo posicionamento
        if(lastPosStatus != posStatus) {
            definePositioning(robots, state, posStatus);
        }

        timeAfterPositioning.restartCounting();
    }

    lastPosStatus = posStatus;

    return strategiesById;
}

std::vector<MindSet> StateInterpreter::defineStrategy(std::vector<RodetasRobot> &robots, RodetasState &state, bool freeBall) {
    chooseStrategies(robots, state, freeBall);

    return strategiesById;
}

std::vector<MindSet> StateInterpreter::definePositioning(std::vector<RodetasRobot>& robots, RodetasState& state, PositionStatus posStatus){

    if(posStatus == PositionStatus::PenaltyHit) {
        definePenaltyHit(robots, state);

    } else if(posStatus == PositionStatus::PenaltyAgainst){
        definePenaltyAgainst(robots, state);

    } else if (posStatus == PositionStatus::Freeball){
        // @TODO
    }

    return strategiesById;
}

// define posicoes para situacao de cobranca de penalti a favor
void StateInterpreter::definePenaltyHit(std::vector<RodetasRobot> & robots, RodetasState & state) {
    strategiesById[robots[0].getId()] = MindSet::PenaltyHitAttackPositioning;
    strategiesById[robots[1].getId()] = MindSet::PenaltyHitDefenderPositioning;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperCenterPositioning;

    // procura por robo mais proximo da bola para bater o penalti
    RodetasRobot closestToBallRobot = getClosestToBallRobot(robots, state);

    if(closestToBallRobot.getId() != 0) {
        MindSet aux = strategiesById[closestToBallRobot.getId()];
        strategiesById[closestToBallRobot.getId()] = MindSet::PenaltyHitAttackPositioning;
        strategiesById[0] = aux;
    }

}

// define posicoes para situacao de defesa de penalti
void StateInterpreter::definePenaltyAgainst(std::vector<RodetasRobot> & robots, RodetasState & state) {



}

void StateInterpreter::chooseStrategies(std::vector<RodetasRobot> & robots, RodetasState & state, bool freeBall) {
    RodetasRobot goalRobot = getRobotByStrategy(MindSet::GoalKeeperStrategy, robots);
    RodetasRobot defenderRobot = getRobotByStrategy(MindSet::DefenderStrategy, robots);
    RodetasRobot attackerRobot = getRobotByStrategy(MindSet::AttackerStrategy, robots);

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
        strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
        strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
    }

    if (freeBall) {
        // se o defensor estiver mais perto da bola entao ele passa a ser o atacante para cobrar free ball
        double distanceDefenderBall = Math::distancePoint(defenderRobot.getSelfState().position, state.ball.position);
        double distanceAttackerBall = Math::distancePoint(attackerRobot.getSelfState().position, state.ball.position);
        if (distanceDefenderBall < distanceAttackerBall) {
            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
        }

        timeHelper.restartCounting();

    } else if (timeHelper.timeOut(2000)) {

        if (attackerRobot.getSelfState().position.x * 1.2 < state.ball.position.x &&
            !(attackerRobot.getSelfState().position.x < state.ball.position.x &&
              defenderRobot.getSelfState().position.x < state.ball.position.x) &&
            !attackerRobot.getRobotStrategyBase().isBlocked() &&
            !defenderRobot.getRobotStrategyBase().isBlocked()) {

            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
        }

        if (attackerRobot.getRobotStrategyBase().isBlocked()) {
            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
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

            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
        }
    }

}

// a estrategia padrao define o robo mais proximo da bola como atacante
void StateInterpreter::defineStandartStrategies(std::vector<RodetasRobot> &robots, RodetasState &state){

    strategiesById[robots[0].getId()] = MindSet::AttackerStrategy;
    strategiesById[robots[1].getId()] = MindSet::DefenderStrategy;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperStrategy;

    // procura por robo mais proximo da bola
    RodetasRobot closestToBallRobot = getClosestToBallRobot(robots, state);

    if(closestToBallRobot.getId() != 0) {
        MindSet aux = strategiesById[closestToBallRobot.getId()];
        strategiesById[closestToBallRobot.getId()] = MindSet::AttackerStrategy;
        strategiesById[0] = aux;
    }
}

// retorna true caso tenha para todos os robos uma estrategia de jogo definida
bool StateInterpreter::doesAllRobotsHaveStrategy(std::vector<RodetasRobot>& robots){

    std::vector<MindSet> strategiesMindSet = getStrategiesMindSet();

    // verifica para cada robo se possui uma estrategia definida
    for(RodetasRobot robot : robots){
        MindSet mindSet = robot.getMindSet();

        auto findMindSetInVector = std::find(strategiesMindSet.begin(), strategiesMindSet.end(), mindSet);

        if ( findMindSetInVector == strategiesMindSet.end()){
            // nao encontrou no vetor
            return false;
        }
    }

    return true;
}

RodetasRobot StateInterpreter::getRobotByStrategy(MindSet mindSet, std::vector<RodetasRobot> &robots) {

    auto found = std::find_if(robots.begin(), robots.end(), [&](RodetasRobot r) {
        return r.getMindSet() == mindSet;
    });

    return *found;
}

RodetasRobot StateInterpreter::getClosestToBallRobot(std::vector<RodetasRobot> & robots, RodetasState & state) {

    // procura por robo mais proximo da bola
    RodetasRobot closestToBallRobot;
    double lowerDistance = 1000;
    for(RodetasRobot& r : robots){
        double distance = Math::distancePoint(r.getSelfState().position, state.ball.position);
        if(distance < lowerDistance){
            closestToBallRobot = r;
            lowerDistance = distance;
        }
    }

    return closestToBallRobot;
}