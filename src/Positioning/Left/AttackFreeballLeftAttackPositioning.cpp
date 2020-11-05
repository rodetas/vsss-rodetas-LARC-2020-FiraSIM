//
// Created by leonardo on 19/10/18.
//

#include "Positioning/Left/AttackFreeballLeftAttackPositioning.h"

vss::WheelsCommand AttackFreeballLeftAttackPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose AttackFreeballLeftAttackPositioning::defineTarget() {

    target = vss::Pose((0.25*(vss::MAX_COORDINATE_X  - 20))+15,103,0);

    return target;
}