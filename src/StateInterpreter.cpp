//
// Created by manoel on 06/05/18.
//

#include "StateInterpreter.h"

StateInterpreter::StateInterpreter() {
    lastPosStatus = PositionStatus::None;
    strategiesById.resize(3);
};

std::vector<MindSet> StateInterpreter::manageStrategyOrPositioning(std::vector<RodetasRobot> &robots, RodetasState &state, bool enabledSwap, bool freeBall, PositionStatus posStatus){

    for (unsigned int j = 0; j < robots.size(); j++) {
        strategiesById[j] = robots[j].getMindSet();
    }

    if(posStatus == PositionStatus::None){
        // garante que nao ocorrerá troca nos primeiros 2 segundos apos um posicionamento
        if(timeAfterPositioning.getElapsedTime() < 2000){
            defineStandartStrategies(robots, state);
        } else if(enabledSwap and timeLastChange.getElapsedTime() > 2000) {
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
        strategiesById[closestToBallRobot.getId()] = MindSet::AttackMiddleAttackPositioning;
        strategiesById[robots[0].getId()] = aux;

    }

}

void StateInterpreter::chooseStrategies(std::vector<RodetasRobot> & robots, RodetasState & state, bool freeBall) {
    // @TODO refatorar essa troca de estrategias
    RodetasRobot goalRobot = getRobotByStrategy(MindSet::GoalKeeperStrategy, robots);
    RodetasRobot defenderRobot = getRobotByStrategy(MindSet::DefenderStrategy, robots);
    RodetasRobot attackerRobot = getRobotByStrategy(MindSet::AttackerStrategy, robots);
    RodetasRobot leftDefenseRobot = getRobotByStrategy(MindSet::DefenderStrategyLeft, robots);
    RodetasRobot rightDefenseRobot = getRobotByStrategy(MindSet::DefenderStrategyRight, robots);
    RodetasRobot attackDefenseRobot = getRobotByStrategy(MindSet::AttackDefenseStrategy, robots);

    if (not leftDefenseRobot.isNull() and not rightDefenseRobot.isNull()){
        if(state.ball.position.x > vss::MAX_COORDINATE_X*0.75){
            // se a bola passou da linha de defesa, torna um robo o defensor
            if(state.ball.projection.y < vss::MAX_COORDINATE_Y/2){
                strategiesById[leftDefenseRobot.getId()] = MindSet::AttackDefenseStrategy;
                strategiesById[rightDefenseRobot.getId()] = MindSet::DefenderStrategyRight;
            } else {
                strategiesById[leftDefenseRobot.getId()] = MindSet::DefenderStrategyLeft;
                strategiesById[rightDefenseRobot.getId()] = MindSet::AttackDefenseStrategy;
            }
            timeLastChange.restartCounting();
        }
    }

    if(not attackDefenseRobot.isNull()){
        if(attackDefenseRobot.getSelfState().position.x < vss::MAX_COORDINATE_X*0.6){
            strategiesById[attackDefenseRobot.getId()] = MindSet::AttackerStrategy;
            if(not rightDefenseRobot.isNull()){
                strategiesById[rightDefenseRobot.getId()] = MindSet::DefenderStrategyRight;
            } else {
                strategiesById[leftDefenseRobot.getId()] = MindSet::DefenderStrategyLeft;
            }
            timeLastChange.restartCounting();
        }
    }

    if (not attackerRobot.isNull() and not defenderRobot.isNull()) {

//        if(attackerRobot.getSelfState().projection.x*1.3 < state.ball.position.x and
//        state.ball.position.x < vss::MAX_COORDINATE_X/2){
//            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategyLeft;
//            strategiesById[defenderRobot.getId()] = MindSet::DefenderStrategyRight;
//        }

        if (state.ball.position.x < vss::MAX_COORDINATE_X / 2 and // bola esta no ataque
        (state.ball.projection.y > 50 && state.ball.projection.y < 80 && state.ball.position.x < defenderRobot.getSelfState().position.x) and // bola esta passando de frente pro gol
        (attackerRobot.getSelfState().position.y > 90 || attackerRobot.getSelfState().position.y < 35) and // robo atacante nao esta de frente pro gol
        (defenderRobot.getSelfState().position.y > 55 and defenderRobot.getSelfState().position.y < 75)) { // defensor esta bem posicionado
            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
            timeLastChange.restartCounting();
            std::cout << "first" << std::endl;
        }

        // define troca quando a bola esta distante para tras do atacante
        if (attackerRobot.getSelfState().position.x * 1.2 < state.ball.position.x and // a bola precisa estar distante do atacante
        !(attackerRobot.getSelfState().position.x < state.ball.position.x && defenderRobot.getSelfState().position.x > state.ball.position.x) and // os dois robos nao podem estar na frente da bola
        state.ball.position.x < vss::MAX_COORDINATE_X/2 and // bola esta no campo de ataque
        !attackerRobot.getRobotStrategyBase().isBlocked() and // atacante nao pode estar bloqueado
        !defenderRobot.getRobotStrategyBase().isBlocked()) { // defensor nao pode estar bloqueado

            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
            timeLastChange.restartCounting();
            std::cout << "second" << std::endl;
        }

        if (attackerRobot.getRobotStrategyBase().isBlocked()) {
            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
            timeLastChange.restartCounting();
            std::cout << "third" << std::endl;
        }

        if(defenderRobot.getSelfState().position.x < vss::MAX_COORDINATE_X*0.65 and
        defenderRobot.getSelfState().distanceFrom(state.ball.position) < 20 and
        defenderRobot.getSelfState().linearSpeed > 10) {
            strategiesById[attackerRobot.getId()] = MindSet::DefenderStrategy;
            strategiesById[defenderRobot.getId()] = MindSet::AttackerStrategy;
            timeLastChange.restartCounting();
            std::cout << "fourth" << std::endl;
        }
    }

//    if(not leftDefenseRobot.isNull() and not rightDefenseRobot.isNull()){
//
//        if(leftDefenseRobot.getSelfState().position.x > vss::MAX_COORDINATE_X * 0.65 and
//        state.ball.position.x > vss::MAX_COORDINATE_X * 0.65){
//            strategiesById[leftDefenseRobot.getId()] = MindSet::AttackerStrategy;
//            strategiesById[rightDefenseRobot.getId()] = MindSet::DefenderStrategy;
//        }
//
//    }


}

// a estrategia padrao define o robo mais proximo da bola como atacante
// parametro fixed define se vai ser levada em consideracao a distancia pra bola ou nao para escolher o atacante
void StateInterpreter::defineStandartStrategies(std::vector<RodetasRobot> &robots, RodetasState &state, bool fixed){

    strategiesById[robots[0].getId()] = MindSet::AttackerStrategy;
    strategiesById[robots[1].getId()] = MindSet::DefenderStrategy;
    strategiesById[robots[2].getId()] = MindSet::GoalKeeperStrategy;

    if(not fixed) {
        // procura por robo mais proximo da bola
        RodetasRobot closestToBallRobot = getClosestRobotTo(robots, state.ball.position);

        if (closestToBallRobot.getId() != 0) {
            MindSet aux = strategiesById[closestToBallRobot.getId()];
            strategiesById[closestToBallRobot.getId()] = MindSet::AttackerStrategy;
            strategiesById[0] = aux;
        }
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

    std::sort(aux.begin(), aux.end(), [&](RodetasRobot a, RodetasRobot b){
       return Math::distancePoint(a.getSelfState().position, point) < Math::distancePoint(b.getSelfState().position, point);
    });

    return aux;
}
