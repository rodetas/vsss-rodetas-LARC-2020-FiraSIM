//
// Created by samuel on 10/10/18.
//

#include "Positioning/Middle/DefenderMiddleAttackPositioning.h"

vss::WheelsCommand DefenderMiddleAttackPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e o mantem virado para a bola
    c = stopStrategy(c, state.ball.position);
    return c;
}

vss::Pose DefenderMiddleAttackPositioning::defineTarget(){
    vss::Pose target((vss::MAX_COORDINATE_X - 20)*0.75, vss::MAX_COORDINATE_Y*0.4, 0);

    return target;
}