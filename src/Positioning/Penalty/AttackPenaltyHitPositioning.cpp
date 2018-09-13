//
// Created by manoel on 31/08/18.
//

#include "Positioning/Penalty/AttackPenaltyHitPositioning.h"

vss::WheelsCommand AttackPenaltyHitPositioning::specificStrategy(vss::WheelsCommand command){

    // @TODO criar metodo para robo parar no ponto
    // @TODO posicionar robo de frente pra bola - possivel aproveitar implementacoes ja existentes na estrategia

    return command;
}

vss::Pose AttackPenaltyHitPositioning::defineTargetAndArrivalOrientation() {
    // @TODO calibrar melhor essa pose de forma que seja uma distancia aceitavel para a bola

    target = vss::Pose(35,65,0);

    return target;
}