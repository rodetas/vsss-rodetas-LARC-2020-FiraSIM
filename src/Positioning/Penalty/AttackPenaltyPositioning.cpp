//
// Created by manoel on 31/08/18.
//

#include "Positioning/Penalty/AttackPenaltyPositioning.h"

vss::WheelsCommand AttackPenaltyPositioning::specificStrategy(vss::WheelsCommand command){

    // @TODO criar metodo para robo parar no ponto
    // @TODO posicionar robo de frente pra bola
    // @TODO permitir que movimentation retorne velocidades mais 'altas' ou mais 'lentas'

    // @TODO remover essas atribuicoes quando for adicionado parametro no movimentation
    command.leftVel *= 0.5;
    command.rightVel *= 0.5;

    return command;
}

vss::Pose AttackPenaltyPositioning::defineTargetAndArrivalOrientation() {
    // @TODO calibrar melhor essa posicao de forma que a distancia para a bola seja aceitavel

    target = vss::Pose(35,65,0);
    arrivalOrientation = vss::Point(0, 65);

    return target;
}