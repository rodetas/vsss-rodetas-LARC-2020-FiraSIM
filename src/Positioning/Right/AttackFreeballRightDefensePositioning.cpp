//
// Created by leonardo on 19/10/18.
//

#include "Positioning/Right/AttackFreeballRightDefensePositioning.h"

vss::WheelsCommand AttackFreeballRightDefensePositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose AttackFreeballRightDefensePositioning::defineTarget() {

    target = vss::Pose((0.75*(vss::MAX_COORDINATE_X - 20))+6,26,0);

    return target;
}