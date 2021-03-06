//
// Created by manoel on 14/09/18.
//

#include "Positioning/Penalty/DefenderPenaltyAgainstPositioning.h"

vss::WheelsCommand DefenderPenaltyAgainstPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que o robo deve parar no ponto e o mantem sempre virado para o nosso gol de defesa
    c = stopStrategy(c, vss::Point((vss::MAX_COORDINATE_X  - 20), vss::MAX_COORDINATE_Y/2));

    return c;
}

vss::Pose DefenderPenaltyAgainstPositioning::defineTarget() {
    vss::Pose target((vss::MAX_COORDINATE_X  - 20)/2-10, vss::MAX_COORDINATE_Y*0.7, 0);

    return target;
}