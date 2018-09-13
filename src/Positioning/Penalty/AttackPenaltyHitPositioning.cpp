//
// Created by manoel on 31/08/18.
//

#include "Positioning/Penalty/AttackPenaltyHitPositioning.h"

vss::WheelsCommand AttackPenaltyHitPositioning::specificStrategy(vss::WheelsCommand command){

    // @TODO criar metodo para robo parar no ponto
    // @TODO posicionar robo de frente pra bola

    return command;
}

vss::Pose AttackPenaltyHitPositioning::defineTargetAndArrivalOrientation() {
    // @TODO calibrar melhor essa posicao de forma que a distancia para a bola seja aceitavel

    target = vss::Pose(35,65,0);

    return target;
}