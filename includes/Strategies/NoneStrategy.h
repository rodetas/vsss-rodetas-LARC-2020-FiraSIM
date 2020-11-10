//
// Created by manoel on 20/10/18.
//

#ifndef SDK_RODETAS_NONESTRATEGY_H
#define SDK_RODETAS_NONESTRATEGY_H

#include "RobotStrategy.h"

class NoneStrategy : public RobotStrategy {

public:

    NoneStrategy();
    vss::WheelsCommand specificStrategy(vss::WheelsCommand) override;
    vss::Pose defineTarget() override;
    float applyUnivectorField(vss::Pose) override;

};

#endif //SDK_RODETAS_NONESTRATEGY_H
