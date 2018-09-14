//
// Created by manoel on 31/08/18.
//

#include "Positioning/Penalty/AttackPenaltyHitPositioning.h"

vss::WheelsCommand AttackPenaltyHitPositioning::specificStrategy(vss::WheelsCommand c){
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose AttackPenaltyHitPositioning::defineTargetAndArrivalOrientation() {
    // @TODO calibrar melhor essa pose de forma que seja uma distancia aceitavel para a bola

    target = vss::Pose(35,65,0);

    return target;
}