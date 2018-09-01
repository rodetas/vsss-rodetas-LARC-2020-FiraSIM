//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_ROBOTPOSITIONING_H
#define SDK_RODETAS_ROBOTPOSITIONING_H

#include <Movements/UnivectorField.h>
#include <Movements/Movimentation.h>
#include <Agent.h>

class RobotPositioning : public Agent {

public:

    vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase) override;
    vss::Pose defineTargetAndArrivalOrientation() override = 0;
    float applyUnivectorField(vss::Pose) override;

private:
    Movimentation movimentation;

};

#endif //SDK_RODETAS_ROBOTPOSITIONING_H
