//
// Created by manoel on 12/09/18.
//

#include "Positioning/Penalty/DefenderPenaltyHitPositioning.h"

vss::WheelsCommand DefenderPenaltyHitPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose DefenderPenaltyHitPositioning::defineTargetAndArrivalOrientation() {

    target = vss::Pose(100,65,0);

    return target;
}