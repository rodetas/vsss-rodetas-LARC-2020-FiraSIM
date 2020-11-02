//
// Created by manoel on 14/09/18.
//

#include "Positioning/Penalty/AttackPenaltyAgainstPositioning.h"

vss::WheelsCommand AttackPenaltyAgainstPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e o mantem virado para o nosso gol de defesa
    c = stopStrategy(c, vss::Point((vss::MAX_COORDINATE_X - 20), vss::MAX_COORDINATE_Y/2));
    return c;
}

vss::Pose AttackPenaltyAgainstPositioning::defineTarget(){
    vss::Pose target((vss::MAX_COORDINATE_X - 20)/2-10, vss::MAX_COORDINATE_Y*0.3, 0);

    return target;
}
