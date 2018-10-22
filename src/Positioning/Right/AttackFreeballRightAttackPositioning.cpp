//
// Created by leonardo on 19/10/18.
//

#include "Positioning/Right/AttackFreeballRightAttackPositioning.h"

vss::WheelsCommand AttackFreeballRightAttackPositioning::specificStrategy(vss::WheelsCommand c) {
    // define que robo deve parar no ponto e estar sempre virado para a bola
    c = stopStrategy(c, state.ball.position);

    return c;
}

vss::Pose AttackFreeballRightAttackPositioning::defineTarget() {

    target = vss::Pose((0.25*vss::MAX_COORDINATE_X)+15,26,0);

    return target;
}
