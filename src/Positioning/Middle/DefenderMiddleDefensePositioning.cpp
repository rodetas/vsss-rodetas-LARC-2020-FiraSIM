//
// Created by samuel on 10/10/18.
//

#include "Positioning/Middle/DefenderMiddleDefensePositioning.h"

vss::WheelsCommand DefenderMiddleDefensePositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e o mantem virado para a bola
    c = stopStrategy(c, state.ball.position);
    return c;
}

vss::Pose DefenderMiddleDefensePositioning::defineTarget(){
    vss::Pose target((vss::MAX_COORDINATE_X - 20)*0.7, vss::MAX_COORDINATE_Y*0.4, 0);

    return target;
}