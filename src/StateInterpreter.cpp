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
        // garante que nao ocorrerá troca nos primeiros 2 segundos apos um posicionamento
        if(timeAfterPositioning.getElapsedTime() < 2000){
            defineStandartStrategies(robots, state);
        } else if(enabledSwap) {
            defineStrategy(robots, state, freeBall);
        }
    } else {
        // garante que uma vez definida as acoes de um robo esta nao sera alterada durante uma mesma requisicao de posicionamento
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

    } else if(posStatus == PositionStatus::MiddleDefense){
        defineMiddleDefense(robots, state);

    } else if(posStatus == PositionStatus::MiddleAttack){
        defineMiddleAttack(robots, state);

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
    RodetasRobot closestToBallRobot = getClosestRobotTo(robots, state.ball.position);

    if(closestToBallRobot.getId() != 0) {
        MindSet aux = strategiesById[closestToBallRobot.getId()];
        strategiesById[closestToBallRobot.getId()] = MindSet::PenaltyHitAttackPositioning;
        strategiesById[0] = aux;
    }

}

// define posicoes para situacao de defesa de penalti
void StateInterpreter::definePenaltyAgainst(std::vector<RodetasRobot> & robots, RodetasState & state) {
    
    strategiesById[robots[0].getId()] = MindSet::PenaltyAgainstAttackPositioning;
    strategiesById[robots[1].getId()] = MindSet::PenaltyAgainstDefenderPositioning;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperCenterPositioning;

    // o robo mais perto do gol sera o goleiro
    RodetasRobot closestToGoal = getClosestRobotTo(robots, vss::Point(vss::MAX_COORDINATE_X, vss::MAX_COORDINATE_Y/2));

    if(closestToGoal.getId() != 2) {
        MindSet aux = strategiesById[closestToGoal.getId()];
        strategiesById[closestToGoal.getId()] = MindSet::GoalKeeperCenterPositioning;
        strategiesById[2] = aux;
    }

}

void StateInterpreter::defineMiddleDefense(std::vector<RodetasRobot> & robots, RodetasState & state) {
    strategiesById[robots[0].getId()] = MindSet::AttackMiddleDefensePositioning;
    strategiesById[robots[1].getId()] = MindSet::DefenderMiddleDefensePositioning;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperCenterPositioning;

}

void StateInterpreter::defineMiddleAttack(std::vector<RodetasRobot> & robots, RodetasState & state) {
    strategiesById[robots[0].getId()] = MindSet::AttackMiddleAttackPositioning;
    strategiesById[robots[1].getId()] = MindSet::DefenderMiddleAttackPositioning;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperCenterPositioning;

    // procura por robo mais proximo da bola para ser o atacante
    RodetasRobot closestToBallRobot = getClosestRobotTo(robots, state.ball.position);
    
    if(closestToBallRobot.getId() != 0){
        MindSet aux = strategiesById[closestToBallRobot.getId()];
        strategiesById[closestToBallRobot.getId()] = MindSet::AttackMiddleDefensePositioning;
        strategiesById[robots[0].getId()] = aux;

    }

}

void StateInterpreter::chooseStrategies(std::vector<RodetasRobot> & robots, RodetasState & state, bool freeBall) {
    // @TODO refatorar essa troca de estrategias
    RodetasRobot goalRobot = getRobotByStrategy(MindSet::GoalKeeperStrategy, robots);
    RodetasRobot defenderRobot = getRobotByStrategy(MindSet::DefenderStrategy, robots);
    RodetasRobot attackerRobot = getRobotByStrategy(MindSet::AttackerStrategy, robots);

    strategiesById[goalRobot.getId()] = goalRobot.getMindSet();
    strategiesById[defenderRobot.getId()] = defenderRobot.getMindSet();
    strategiesById[attackerRobot.getId()] = attackerRobot.getMindSet();

    //Troca defensor por atacante
    if (not attackerRobot.isNull() and not defenderRobot.isNull() and
        state.ball.position.x < vss::MAX_COORDINATE_X / 2 &&
        (state.ball.projection.y > 50 && state.ball.projection.y < 80 &&
          state.ball.position.x < defenderRobot.getSelfState().position.x) && // Bola dentro da area
        (attackerRobot.getSelfState().position.y > 90 || attackerRobot.getSelfState().position.y < 35) &&
        (defenderRobot.getSelfState().position.y > 55) &&
        (defenderRobot.getSelfState().position.y < 75)) // se o defensor esta posicionado
    {
        strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
        strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
    }

    if (freeBall) {
        defineStandartStrategies(robots, state);
        timeHelper.restartCounting();

    } else if (timeHelper.timeOut(2000)) {

        if(not attackerRobot.isNull() and not defenderRobot.isNull()) {

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
        }
    }
}

// a estrategia padrao define o robo mais proximo da bola como atacante
void StateInterpreter::defineStandartStrategies(std::vector<RodetasRobot> &robots, RodetasState &state){

    strategiesById[robots[0].getId()] = MindSet::AttackerStrategy;
    strategiesById[robots[1].getId()] = MindSet::DefenderStrategy;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperStrategy;

    // procura por robo mais proximo da bola
    RodetasRobot closestToBallRobot = getClosestRobotTo(robots, state.ball.position);

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

    if (found == robots.end()){
        return RodetasRobot();
    }

    return *found;
}

// metodo que retorna o robo mais proximo do ponto enviado por parametro
RodetasRobot StateInterpreter::getClosestRobotTo(std::vector<RodetasRobot> & robots, vss::Point point) {

    // procura por robo mais proximo do ponto
    RodetasRobot closestRobot;
    double lowerDistance = 1000;
    for(RodetasRobot& r : robots){
        double distance = Math::distancePoint(r.getSelfState().position, point);
        if(distance < lowerDistance){
            closestRobot = r;
            lowerDistance = distance;
        }
    }

    return closestRobot;
}

// retorna um vetor com os robos ordenado por distancia
std::vector<RodetasRobot> StateInterpreter::getClosestRobots(std::vector<RodetasRobot>& robots, vss::Point point){

    std::vector<RodetasRobot> aux = robots;

    std::sort(aux.begin(), aux.end(), [&](const RodetasRobot& a, const RodetasRobot& b){
       return Math::distancePoint(a.getSelfState().position, point) < Math::distancePoint(b.getSelfState().position, point);
    });

    return aux;
}