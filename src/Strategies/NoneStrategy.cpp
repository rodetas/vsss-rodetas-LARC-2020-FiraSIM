//
// Created by manoel on 20/10/18.
//

#include "NoneStrategy.h"

NoneStrategy::NoneStrategy() = default;

vss::WheelsCommand NoneStrategy::specificStrategy(vss::WheelsCommand c) {
    return (vss::WheelsCommand(0,0));
}

vss::Pose NoneStrategy::defineTarget() {
    return (vss::Pose(0,0,0));
}

float NoneStrategy::applyUnivectorField(vss::Pose pose) {
    return 0;
}
