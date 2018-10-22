//
// Created by leonardo on 19/10/18.
//

#include "Positioning/Left/AttackFreeballLeftDefensePositioning.h"

vss::WheelsCommand AttackFreeballLeftDefensePositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose AttackFreeballLeftDefensePositioning::defineTarget() {

    target = vss::Pose((0.75*vss::MAX_COORDINATE_X)+6,103,0);
    return target;
}