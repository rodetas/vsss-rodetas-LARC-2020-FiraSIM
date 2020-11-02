//
// Created by samuel on 10/10/18.
//

#include "Positioning/Middle/AttackMiddleAttackPositioning.h"

vss::WheelsCommand AttackMiddleAttackPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e o mantem virado para a bola
    c = stopStrategy(c, state.ball.position);
    return c;
}

vss::Pose AttackMiddleAttackPositioning::defineTarget(){
    vss::Pose target((vss::MAX_COORDINATE_X - 20)/2+4, vss::MAX_COORDINATE_Y*0.5, 0);

    return target;
}